import torch
from torch.testing._internal.common_utils import TestCase
from torch.testing._internal.optests import opcheck
import pytest
from scipy import special

import torch_bessel


def reference_modified_bessel_k0(z, singularity=None):
    device = z.device
    dtype = z.dtype
    if dtype is torch.chalf:
        z = z.to(torch.cfloat)
    out = special.kv(0.0, z.detach().cpu()).to(device).to(dtype)
    if singularity is not None:
        out = out.where(z != 0, singularity)
    return out


def reference_modified_bessel_k1(z):
    device = z.device
    dtype = z.dtype
    if dtype is torch.chalf:
        z = z.to(torch.cfloat)
    out = special.kv(1.0, z.detach().cpu()).to(device).to(dtype)
    return out


class TestBesselK0(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_z(*size, dtype=None):
            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.randn(size, **kwargs).abs()
            imag = torch.randn(size, **kwargs)
            return torch.complex(real, imag)

        out = [
            [make_z(50, dtype=torch.double)],
            [make_z(50, dtype=torch.double).real],
            [make_z(50)],
            [make_z(50).real],
            # [torch.tensor(70.1162 + 89.0190j)],  # problematic input, need to investigate
        ]
        if device == "cuda":
            # half precision is only supported on CUDA
            out.append([make_z(50, dtype=torch.half)])

        return out

    def grid_inputs(self, device, *, requires_grad=False):
        def make_z(*args, dtype=torch.float):
            real = torch.tensor([0, *torch.logspace(*args, dtype=torch.double)])
            imag = torch.logspace(*args, dtype=torch.double)

            # Don't test on subnormal numbers, since the AMOS code doesn't consider them
            real[real < torch.finfo(dtype).tiny] = 0.0
            imag[imag < torch.finfo(dtype).tiny] = 0.0

            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.tensor(real, **kwargs)
            imag = torch.tensor([*(-imag.flip(0)), 0, *imag], **kwargs)
            real, imag = real[:, None], imag[None, :]
            return torch.complex(real, imag)

        out = [
            [make_z(-350, 350, 75, dtype=torch.double)],
            [make_z(-50, 50, 75)],
            # [make_z(-5, 5, 75)],  # problematic input, need to investigate
            [make_z(-50, 50, 75), 1.0],
            [make_z(-50, 50, 75), torch.randn((76, 151), device=device)],
        ]
        if device == "cuda":
            # half precision is only supported on CUDA
            out.append([make_z(-5, 5, 75, dtype=torch.half)])
        return out

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
            if expected.dtype in {torch.float, torch.cfloat, torch.chalf}:
                # ierr = 4, complete loss of significance
                expected[args[0].abs() > 4194303.98419452] = torch.nan
                # ierr = 2, overflow
                mask = (args[0].abs() < 1.1754944e-35) & (args[0] != 0)
                if expected.is_complex():
                    expected[mask] = torch.nan
                    expected[mask & (args[0].imag == 0) & (args[0] != 0)] = torch.inf
                else:
                    expected[mask & (args[0] != 0)] = torch.inf
            # if expected.ndim == 2:
            #     print(result[57:61,0:4])
            #     print(expected[57:61,0:4])
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


@pytest.mark.parametrize(
    "singularity, in_dims",
    [
        (None, (0, None)),
        (0.0, (0, None)),
        ((4, 3), (0, 1)),
    ],
)
def test_vmap(singularity, in_dims):
    z = torch.randn(3, 4).abs() + torch.randn(3, 4) * 1j
    if isinstance(singularity, tuple):
        singularity = torch.randn(singularity)
    func = torch.func.vmap(torch_bessel.ops.modified_bessel_k0, in_dims=in_dims)
    out = func(z, singularity)
    if not isinstance(singularity, torch.Tensor):
        expected = torch_bessel.ops.modified_bessel_k0(z, singularity)
    else:
        expected = torch_bessel.ops.modified_bessel_k0(z, singularity.t())
    torch.testing.assert_close(out, expected)


class TestBesselK1(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_z(*size, dtype=None):
            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.randn(size, **kwargs).abs()
            imag = torch.randn(size, **kwargs)
            return torch.complex(real, imag)

        out = [
            [make_z(50, dtype=torch.double)],
            [make_z(50, dtype=torch.double).real],
            [make_z(50)],
            [make_z(50).real],
            # [torch.tensor(70.1162 + 89.0190j)],  # problematic input, need to investigate
        ]
        if device == "cuda":
            # half precision is only supported on CUDA
            out.append([make_z(50, dtype=torch.half)])

        return out

    def grid_inputs(self, device, *, requires_grad=False):
        def make_z(*args, dtype=torch.float):
            real = torch.tensor([0, *torch.logspace(*args, dtype=torch.double)])
            imag = torch.logspace(*args, dtype=torch.double)

            # Don't test on subnormal numbers, since the AMOS code doesn't consider them
            real[real < torch.finfo(dtype).tiny] = 0.0
            imag[imag < torch.finfo(dtype).tiny] = 0.0

            kwargs = dict(dtype=dtype, device=device, requires_grad=requires_grad)
            real = torch.tensor(real, **kwargs)
            imag = torch.tensor([*(-imag.flip(0)), 0, *imag], **kwargs)
            real, imag = real[:, None], imag[None, :]
            return torch.complex(real, imag)

        out = [
            [make_z(-350, 350, 75, dtype=torch.double)],
            [make_z(-50, 50, 75)],
            # [make_z(-5, 5, 75)],  # problematic input, need to investigate
        ]
        if device == "cuda":
            # half precision is only supported on CUDA
            out.append([make_z(-5, 5, 75, dtype=torch.half)])
        return out

    def _test_correctness(self, device):
        samples = self.sample_inputs(device) + self.grid_inputs(device)
        for args in samples:
            result = torch_bessel.ops.modified_bessel_k1(*args)
            expected = reference_modified_bessel_k1(*args)
            if expected.dtype in {torch.float, torch.cfloat, torch.chalf}:
                # ierr = 4, complete loss of significance
                expected[args[0].abs() > 4194303.98419452] = torch.nan
                # ierr = 2, overflow
                mask = (args[0].abs() < 1.1754944e-35) & (args[0] != 0)
                if expected.is_complex():
                    expected[mask] = torch.nan
                    expected[mask & (args[0].imag == 0) & (args[0] != 0)] = torch.inf
                else:
                    expected[mask & (args[0] != 0)] = torch.inf
            # if expected.ndim == 2:
            #     print(result[57:61,0:4])
            #     print(expected[57:61,0:4])
            torch.testing.assert_close(result, expected, equal_nan=True)

    def test_correctness_cpu(self):
        self._test_correctness("cpu")

    @pytest.mark.skipif(not torch.cuda.is_available(), reason="requires cuda")
    def test_correctness_cuda(self):
        self._test_correctness("cuda")

    def _opcheck(self, device):
        # Use opcheck to check for incorrect usage of operator registration APIs
        samples = self.sample_inputs(device, requires_grad=False)
        for args in samples:
            if not args[0].is_complex():
                continue
            opcheck(
                torch.ops.torch_bessel.modified_bessel_k1_complex_forward.default, args
            )

    def test_opcheck_cpu(self):
        self._opcheck("cpu")

    @pytest.mark.skipif(not torch.cuda.is_available(), reason="requires cuda")
    def test_opcheck_cuda(self):
        self._opcheck("cuda")


@pytest.mark.parametrize("in_dims", [0, 1])
def test_vmap_k1(in_dims):
    z = torch.randn(3, 4).abs() + torch.randn(3, 4) * 1j
    func = torch.func.vmap(torch_bessel.ops.modified_bessel_k1, in_dims=in_dims)
    out = func(z)
    expected = torch_bessel.ops.modified_bessel_k1(z)
    if in_dims == 1:
        expected = expected.t()
    torch.testing.assert_close(out, expected)
