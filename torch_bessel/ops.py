import torch
from torch import Tensor

__all__ = ["bessel_k0"]


def bessel_k0(z: Tensor) -> Tensor:
    if z.requires_grad:
        return torch.ops.torch_bessel.bessel_k0_forward_backward.default(z)[0]
    return torch.ops.torch_bessel.bessel_k0_forward.default(z)


@torch.library.register_fake("torch_bessel::bessel_k0_forward")
def _(z):
    return torch.empty_like(z)


@torch.library.register_fake("torch_bessel::bessel_k0_forward_backward")
def _(z):
    return torch.empty_like(z), torch.empty_like(z)


def bessel_k0_backward(ctx, grad, _):
    if ctx.needs_input_grad[0]:
        return grad * ctx.saved_tensors[0]
    return None


def bessel_k0_setup_context(ctx, inputs, output):
    if ctx.needs_input_grad[0]:
        ctx.save_for_backward(output[-1])


torch.library.register_autograd(
    "torch_bessel::bessel_k0_forward_backward",
    bessel_k0_backward,
    setup_context=bessel_k0_setup_context,
)
