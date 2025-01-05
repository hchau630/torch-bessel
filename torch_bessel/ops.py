import torch
from torch import Tensor

__all__ = ["bessel_k"]


def bessel_k(nu: Tensor, z: Tensor) -> Tensor:
    if z.requires_grad:
        return torch.ops.torch_bessel.bessel_k_forward_backward.default(nu, z)[0]
    return torch.ops.torch_bessel.bessel_k_forward.default(nu, z)


# Registers a FakeTensor kernel (aka "meta kernel", "abstract impl")
# that describes what the properties of the output Tensor are given
# the properties of the input Tensor. The FakeTensor kernel is necessary
# for the op to work performantly with torch.compile.
@torch.library.register_fake("torch_bessel::bessel_k_forward")
def _(nu, z):
    torch._check(nu.device == z.device)
    shape = torch.broadcast_shapes(nu.shape, z.shape)
    dtype = torch.promote_types(nu.dtype, z.dtype)
    out = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    return out


# Registers a FakeTensor kernel (aka "meta kernel", "abstract impl")
# that describes what the properties of the output Tensor are given
# the properties of the input Tensor. The FakeTensor kernel is necessary
# for the op to work performantly with torch.compile.
@torch.library.register_fake("torch_bessel::bessel_k_forward_backward")
def _(nu, z):
    torch._check(nu.device == z.device)
    shape = torch.broadcast_shapes(nu.shape, z.shape)
    dtype = torch.promote_types(nu.dtype, z.dtype)
    out1 = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    out2 = torch.empty(shape, dtype=dtype, device=z.device, layout=z.layout)
    return out1, out2


def _backward(ctx, grad, _):
    grad_v, grad_z = None, None
    if ctx.needs_input_grad[0]:
        raise NotImplementedError("gradient of bessel_k w.r.t nu is not implemented.")
    if ctx.needs_input_grad[1]:
        grad_z = ctx.saved_tensors[0] * grad
    return grad_v, grad_z


def _setup_context(ctx, inputs, output):
    if ctx.needs_input_grad[0]:
        raise NotImplementedError("gradient of bessel_k w.r.t nu is not implemented.")
    if ctx.needs_input_grad[1]:
        ctx.save_for_backward(output[-1])


# This adds training support for the operator. You must provide us
# the backward formula for the operator and a `setup_context` function
# to save values to be used in the backward.
torch.library.register_autograd(
    "torch_bessel::bessel_k_forward_backward", _backward, setup_context=_setup_context
)


# def _backward(ctx, grad):
#     grad_v, grad_z = None, None
#     if ctx.needs_input_grad[0]:
#         raise NotImplementedError("gradient of BesselK w.r.t nu is not implemented.")
#     if ctx.needs_input_grad[1]:
#         v, z, output = ctx.saved_tensors
#         # dK_v(z)dz = -K_{v-1}(z) - v/z * K_v(z)
#         grad_z = -torch.ops.torch_bessel.bessel_k_forward.default(v - 1, z) - v / z * output
#         # conjugate the gradient for complex inputs, to understand this
#         # see https://pytorch.org/docs/stable/notes/autograd.html#complex-autograd-doc
#         grad_z = grad_z.conj().mul_(grad)
#     return grad_v, grad_z


# def _setup_context(ctx, inputs, output):
#     if ctx.needs_input_grad[0]:
#         raise NotImplementedError("gradient of BesselK w.r.t nu is not implemented.")
#     if ctx.needs_input_grad[1]:
#         ctx.save_for_backward(*inputs, output)


# # This adds training support for the operator. You must provide us
# # the backward formula for the operator and a `setup_context` function
# # to save values to be used in the backward.
# torch.library.register_autograd(
#     "torch_bessel::bessel_k_forward", _backward, setup_context=_setup_context
# )
