import torch
from torch.testing._internal.common_utils import TestCase
from torch.testing._internal.optests import opcheck
import unittest
from scipy import special

import torch_bessel


def reference_bessel_k0(z):
    device = z.device
    return special.kv(0.0, z.detach().cpu()).to(device)


class TestBesselK0(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_z(*size, dtype=None):
            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.randn(size, **kwargs).abs()
            imag = torch.randn(size, **kwargs)
            return torch.complex(real, imag)

        return [
            [make_z(50, dtype=torch.double)],
            [make_z(50, dtype=torch.double).real],
            [make_z(50)],
            [make_z(50).real],
        ]

    def grid_inputs(self, device, *, requires_grad=False):
        def make_z(*args, dtype=torch.float):
            real = torch.tensor([0, *torch.logspace(*args, dtype=torch.double)])
            imag = torch.logspace(*args, dtype=torch.double)

            # Don't test on subnormal numbers, since the AMOS code does not consider them
            real[real < torch.finfo(dtype).tiny] = 0.0
            imag[imag < torch.finfo(dtype).tiny] = 0.0

            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.tensor(real, **kwargs)
            imag = torch.tensor([*(-imag.flip(0)), 0, *imag], **kwargs)
            real, imag = real[:, None], imag[None, :]
            return torch.complex(real, imag)

        return [
            [make_z(-350, 350, 75, dtype=torch.double)],
            [make_z(-50, 50, 75)],
        ]

    def _test_correctness(self, device):
        samples = (
            self.sample_inputs(device)
            + self.grid_inputs(device)
            + self.sample_inputs(device, requires_grad=True)
            + self.grid_inputs(device, requires_grad=True)
        )
        for args in samples:
            result = torch_bessel.ops.bessel_k0(*args)
            expected = reference_bessel_k0(*args)
            if expected.dtype in {torch.float, torch.complex64}:
                # ierr = 4, complete loss of significance
                expected[args[0].abs() > 4194303.98419452] = torch.nan
                # ierr = 2, overflow
                mask = args[0].abs() < 1.1754944e-35
                if expected.dtype == torch.complex64:
                    expected[mask] = torch.nan
                    expected[mask & (args[0].imag == 0) & (args[0] != 0)] = torch.inf
                else:
                    expected[mask & (args[0] != 0)] = torch.inf
            torch.testing.assert_close(result, expected, equal_nan=True)

    def test_correctness_cpu(self):
        self._test_correctness("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_correctness_cuda(self):
        self._test_correctness("cuda")

    def _test_gradients(self, device):
        samples = self.sample_inputs(device, requires_grad=True)
        for args in samples:
            if (
                args[0].dtype in {torch.double, torch.complex128}
                and args[0].requires_grad
            ):
                torch.autograd.gradcheck(torch_bessel.ops.bessel_k0, args)

    def test_gradients_cpu(self):
        self._test_gradients("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_gradients_cuda(self):
        self._test_gradients("cuda")

    def _opcheck(self, device):
        # Use opcheck to check for incorrect usage of operator registration APIs
        samples = self.sample_inputs(device, requires_grad=False)
        samples.extend(self.sample_inputs(device, requires_grad=True))
        for args in samples:
            opcheck(torch.ops.torch_bessel.bessel_k0_forward_backward.default, args)

    def test_opcheck_cpu(self):
        self._opcheck("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_opcheck_cuda(self):
        self._opcheck("cuda")


if __name__ == "__main__":
    unittest.main()
