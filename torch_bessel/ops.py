import torch
from torch import Tensor

__all__ = ["bessel_k", "bessel_k0"]


def bessel_k(nu: Tensor, z: Tensor) -> Tensor:
    if z.requires_grad:
        return torch.ops.torch_bessel.bessel_k_forward_backward.default(nu, z)[0]
    return torch.ops.torch_bessel.bessel_k_forward.default(nu, z)


def bessel_k0(z: Tensor) -> Tensor:
    if z.requires_grad:
        return torch.ops.torch_bessel.bessel_k0_forward_backward.default(z)[0]
    return torch.ops.torch_bessel.bessel_k0_forward.default(z)


@torch.library.register_fake("torch_bessel::bessel_k_forward")
def _(nu, z):
    torch._check(nu.device == z.device)
    shape = torch.broadcast_shapes(nu.shape, z.shape)
    dtype = torch.promote_types(nu.dtype, z.dtype)
    out = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    return out


@torch.library.register_fake("torch_bessel::bessel_k_forward_backward")
def _(nu, z):
    torch._check(nu.device == z.device)
    shape = torch.broadcast_shapes(nu.shape, z.shape)
    dtype = torch.promote_types(nu.dtype, z.dtype)
    out1 = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    out2 = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    return out1, out2


@torch.library.register_fake("torch_bessel::bessel_k0_forward")
def _(z):
    return torch.empty_like(z)


@torch.library.register_fake("torch_bessel::bessel_k0_forward_backward")
def _(z):
    return torch.empty_like(z), torch.empty_like(z)


def bessel_k_backward(ctx, grad, _):
    grad_v, grad_z = None, None
    if ctx.needs_input_grad[0]:
        raise NotImplementedError("gradient of bessel_k w.r.t nu is not implemented.")
    if ctx.needs_input_grad[1]:
        grad_z = grad * ctx.saved_tensors[0]
    return grad_v, grad_z


def bessel_k_setup_context(ctx, inputs, output):
    if ctx.needs_input_grad[0]:
        raise NotImplementedError("gradient of bessel_k w.r.t nu is not implemented.")
    if ctx.needs_input_grad[1]:
        ctx.save_for_backward(output[-1])


def bessel_k0_backward(ctx, grad, _):
    if ctx.needs_input_grad[0]:
        return grad * ctx.saved_tensors[0]
    return None


def bessel_k0_setup_context(ctx, inputs, output):
    if ctx.needs_input_grad[0]:
        ctx.save_for_backward(output[-1])


torch.library.register_autograd(
    "torch_bessel::bessel_k_forward_backward",
    bessel_k_backward,
    setup_context=bessel_k_setup_context,
)

torch.library.register_autograd(
    "torch_bessel::bessel_k0_forward_backward",
    bessel_k0_backward,
    setup_context=bessel_k0_setup_context,
)
