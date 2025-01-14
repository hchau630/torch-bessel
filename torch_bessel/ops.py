from pathlib import Path

import torch
from torch import Tensor

__all__ = ["modified_bessel_k0"]

# load C extension before calling torch.library API, see
# https://pytorch.org/tutorials/advanced/cpp_custom_ops.html
so_dir = Path(__file__).parent
so_files = list(so_dir.glob("_C*.so"))
assert (
    len(so_files) == 1
), f"Expected one _C*.so file at {so_dir}, found {len(so_files)}"
torch.ops.load_library(so_files[0])


class ModifiedBesselK0(torch.autograd.Function):
    @staticmethod
    def forward(x):
        return torch.special.modified_bessel_k0(x)

    @staticmethod
    def setup_context(ctx, inputs, _):
        if ctx.needs_input_grad[0]:
            ctx.save_for_backward(*inputs)
        ctx.set_materialize_grads(False)

    @staticmethod
    def backward(ctx, grad):
        if grad is None or not ctx.needs_input_grad[0]:
            return None

        (x,) = ctx.saved_tensors
        return -torch.special.modified_bessel_k1(x).mul_(grad)


def modified_bessel_k0(z: Tensor) -> Tensor:
    if not z.is_complex():
        return ModifiedBesselK0.apply(z)
    if not z.requires_grad:
        return torch.ops.torch_bessel.modified_bessel_k0_complex_forward.default(z)
    return torch.ops.torch_bessel.modified_bessel_k0_complex_forward_backward.default(
        z
    )[0]


@torch.library.register_fake("torch_bessel::modified_bessel_k0_complex_forward")
def _(z):
    return torch.empty_like(z)


@torch.library.register_fake(
    "torch_bessel::modified_bessel_k0_complex_forward_backward"
)
def _(z):
    return torch.empty_like(z), torch.empty_like(z)


def modified_bessel_k0_backward(ctx, grad, _):
    if ctx.needs_input_grad[0]:
        return grad * ctx.saved_tensors[0]
    return None


def modified_bessel_k0_setup_context(ctx, inputs, output):
    if ctx.needs_input_grad[0]:
        ctx.save_for_backward(output[-1])


torch.library.register_autograd(
    "torch_bessel::modified_bessel_k0_complex_forward_backward",
    modified_bessel_k0_backward,
    setup_context=modified_bessel_k0_setup_context,
)
