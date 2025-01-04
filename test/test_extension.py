import torch
from torch.testing._internal.common_utils import TestCase
from torch.testing._internal.optests import opcheck
import unittest
from scipy import special

import torch_bessel


def reference_besselk(nu, z):
    return special.kv(nu, z)


class TestBesselK(TestCase):
    def sample_inputs(self, device, *, requires_grad=False):
        def make_nu(*size):
            return torch.randn(size, device=device, requires_grad=requires_grad)

        def make_z(*size):
            return torch.complex(
                *torch.randn((2, *size), device=device, requires_grad=requires_grad)
            )

        def make_nondiff_nu(*size):
            return torch.randn(size, device=device, requires_grad=False)

        def make_nondiff_z(*size):
            return torch.complex(
                *torch.randn((2, *size), device=device, requires_grad=False)
            )

        return [[make_nondiff_nu(20), make_nondiff_z(20)]]

    def _test_correctness(self, device):
        samples = self.sample_inputs(device)
        for args in samples:
            print(f"{args=}")
            result = torch_bessel.ops.besselk(*args)
            expected = reference_besselk(*args)
            print(f"{result=}")
            print(f"{expected=}")
            torch.testing.assert_close(result, expected)

    def test_correctness_cpu(self):
        self._test_correctness("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_correctness_cuda(self):
        self._test_correctness("cuda")

    def _test_gradients(self, device):
        samples = self.sample_inputs(device, requires_grad=True)
        for args in samples:
            diff_tensors = [
                a for a in args if isinstance(a, torch.Tensor) and a.requires_grad
            ]
            out = torch_bessel.ops.besselk(*args)
            grad_out = torch.randn_like(out)
            result = torch.autograd.grad(out, diff_tensors, grad_out)

            out = reference_besselk(*args)
            expected = torch.autograd.grad(out, diff_tensors, grad_out)

            torch.testing.assert_close(result, expected)

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
            opcheck(torch.ops.torch_bessel.besselk.default, args)

    def test_opcheck_cpu(self):
        self._opcheck("cpu")

    @unittest.skipIf(not torch.cuda.is_available(), "requires cuda")
    def test_opcheck_cuda(self):
        self._opcheck("cuda")


if __name__ == "__main__":
    unittest.main()
