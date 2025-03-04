import torch
from torch.testing._internal.common_utils import TestCase
from torch.testing._internal.optests import opcheck
import pytest
from scipy import special

import torch_bessel


def reference_modified_bessel_k0(z, singularity=None):
    device = z.device
    out = special.kv(0.0, z.detach().cpu()).to(device)
    if singularity is not None:
        out = out.where(z != 0, singularity)
    return out


class TestBesselK0(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_z(*size, dtype=None):
            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.randn(size, **kwargs)
            imag = torch.randn(size, **kwargs)
            return torch.complex(real, imag)

        return [
            [make_z(50, dtype=torch.double)],
            [make_z(50, dtype=torch.double).real.abs()],
            [make_z(50)],
            [make_z(50).real.abs()],
        ]

    def grid_inputs(self, device, *, requires_grad=False):
        def make_z(*args, dtype=torch.float):
            real = torch.logspace(*args, dtype=torch.double)
            imag = torch.logspace(*args, dtype=torch.double)

            # Don't test on subnormal numbers, since the AMOS code doesn't consider them
            real[real < torch.finfo(dtype).tiny] = 0.0
            imag[imag < torch.finfo(dtype).tiny] = 0.0

            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.tensor([*(-real.flip(0)), 0, *real], **kwargs)
            imag = torch.tensor([*(-imag.flip(0)), 0, *imag], **kwargs)
            real, imag = real[:, None], imag[None, :]
            return torch.complex(real, imag)

        return [
            [make_z(-350, 350, 75, dtype=torch.double)],
            [make_z(-50, 50, 75)],
            [make_z(-50, 50, 75), 1.0],
            [make_z(-50, 50, 75), torch.randn((151, 151), device=device)],
        ]

    def _test_correctness(self, device):
        samples = (
            self.sample_inputs(device)
            + self.grid_inputs(device)
            + self.sample_inputs(device, requires_grad=True)
            + self.grid_inputs(device, requires_grad=True)
        )
        for args in samples:
            result = torch_bessel.ops.modified_bessel_k0(*args)
            expected = reference_modified_bessel_k0(*args)

            # Currently we do not handle inputs on the negative real line
            if torch.is_complex(args[0]):
                expected[(args[0].imag == 0) & (args[0].real < 0)] = torch.nan
            else:
                expected[args[0] < 0] = torch.nan

            # scipy uses double precision algorithm for single precision inputs,
            # so we need to manually set the expected overflow behavior.
            if expected.dtype in {torch.float, torch.complex64}:
                # ierr = 4, complete loss of significance
                expected[args[0].abs() > 4194303.98419452] = torch.nan
                # ierr = 2, overflow
                mask = (args[0].abs() < 1.1754944e-35) & (args[0] != 0)
                if expected.dtype == torch.complex64:
                    expected[mask] = torch.nan
                    expected[mask & (args[0].imag == 0) & (args[0] != 0)] = torch.inf
                    # for large enough abs(z) in the left-half complex plane there is
                    # overflow such that NaN instead of Inf is returned, but not sure
                    # the exact condition
                    expected[(args[0].real < 0) & expected.isinf()] = torch.nan
                else:
                    expected[mask & (args[0] != 0)] = torch.inf

            torch.testing.assert_close(result, expected, equal_nan=True)

    def test_correctness_cpu(self):
        self._test_correctness("cpu")

    @pytest.mark.skipif(not torch.cuda.is_available(), reason="requires cuda")
    def test_correctness_cuda(self):
        self._test_correctness("cuda")

    def _test_gradients(self, device):
        samples = self.sample_inputs(device, requires_grad=True)
        for args in samples:
            if (
                args[0].dtype in {torch.double, torch.complex128}
                and args[0].requires_grad
            ):
                torch.autograd.gradcheck(torch_bessel.ops.modified_bessel_k0, args)

    def test_gradients_cpu(self):
        self._test_gradients("cpu")

    @pytest.mark.skipif(not torch.cuda.is_available(), reason="requires cuda")
    def test_gradients_cuda(self):
        self._test_gradients("cuda")

    def _opcheck(self, device):
        # Use opcheck to check for incorrect usage of operator registration APIs
        samples = self.sample_inputs(device, requires_grad=False)
        samples.extend(self.sample_inputs(device, requires_grad=True))
        for args in samples:
            if not args[0].is_complex():
                continue
            opcheck(
                torch.ops.torch_bessel.modified_bessel_k0_complex_forward_backward.default,
                args,
            )

    def test_opcheck_cpu(self):
        self._opcheck("cpu")

    @pytest.mark.skipif(not torch.cuda.is_available(), reason="requires cuda")
    def test_opcheck_cuda(self):
        self._opcheck("cuda")
