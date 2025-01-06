import torch
from torch.testing._internal.common_utils import TestCase
from torch.testing._internal.optests import opcheck
import unittest
from scipy import special

import torch_bessel


def reference_bessel_k(nu, z):
    device = z.device
    return special.kv(nu.cpu(), z.detach().cpu()).to(device)


class TestBesselK(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_nu(*size, dtype=None):
            # current implementation does not support gradient w.r.t nu
            return torch.randn(size, device=device, requires_grad=False, dtype=dtype)

        def make_z(*size, dtype=None):
            return torch.complex(
                *torch.randn(
                    (2, *size), device=device, requires_grad=requires_grad, dtype=dtype
                )
            )

        def make_nondiff_z(*size, dtype=None):
            return torch.complex(
                *torch.randn(
                    (2, *size), device=device, requires_grad=False, dtype=dtype
                )
            )

        return [
            [make_nu(5, dtype=torch.double), make_z(5, dtype=torch.double)],
            [make_nu(5, dtype=torch.double), make_z(5, dtype=torch.double).abs()],
            [make_nu(20), make_z(20, dtype=torch.double)],
            [make_nu(20), make_z(20, dtype=torch.double).real],
            [make_nu(20), make_z(20)],
            [make_nu(20), make_z(20).real],
            [make_nu(20), make_nondiff_z(20)],
            [make_nu(20), make_nondiff_z(20).real],
        ]

    def _test_correctness(self, device):
        samples = self.sample_inputs(device)
        for args in samples:
            result = torch_bessel.ops.bessel_k(*args)
            expected = reference_bessel_k(*args)
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
                args[0].dtype == torch.double
                and args[1].dtype in {torch.double, torch.complex128}
                and args[1].requires_grad
            ):
                torch.autograd.gradcheck(torch_bessel.ops.bessel_k, args)

    def test_gradients_cpu(self):
        self._test_gradients("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_gradients_cuda(self):
        self._test_gradients("cuda")

    def _opcheck(self, device):
        # Use opcheck to check for incorrect usage of operator registration APIs
        samples = self.sample_inputs(device, requires_grad=True)
        samples.extend(self.sample_inputs(device, requires_grad=False))
        for args in samples:
            opcheck(torch.ops.torch_bessel.bessel_k_forward_backward.default, args)

    def test_opcheck_cpu(self):
        self._opcheck("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_opcheck_cuda(self):
        self._opcheck("cuda")


if __name__ == "__main__":
    unittest.main()
