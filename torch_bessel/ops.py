import torch
from torch import Tensor

__all__ = ["besselk"]


def besselk(nu: Tensor, z: Tensor) -> Tensor:
    return torch.ops.torch_bessel.besselk.default(nu, z)


# Registers a FakeTensor kernel (aka "meta kernel", "abstract impl")
# that describes what the properties of the output Tensor are given
# the properties of the input Tensor. The FakeTensor kernel is necessary
# for the op to work performantly with torch.compile.
@torch.library.register_fake("torch_bessel::besselk")
def _(nu, z):
    torch._check(nu.device == z.device)
    return torch.empty(
        torch.broadcast_shapes(nu.shape, z.shape),
        dtype=torch.complex64,
        device=z.device,
        layout=z.layout,
    )


# def _backward(ctx, grad):
#     a, b = ctx.saved_tensors
#     grad_a, grad_b, grad_c = None, None, None
#     if ctx.needs_input_grad[0]:
#         grad_a = torch.ops.torch_bessel.mymul.default(grad, b)
#     if ctx.needs_input_grad[1]:
#         grad_b = torch.ops.torch_bessel.mymul.default(grad, a)
#     if ctx.needs_input_grad[2]:
#         grad_c = torch.ops.torch_bessel.mymul.default(grad, torch.ones_like(a))
#     return grad_a, grad_b, grad_c


# def _setup_context(ctx, inputs, output):
#     a, b, _ = inputs
#     saved_a, saved_b = None, None
#     if ctx.needs_input_grad[0]:
#         saved_b = b
#     if ctx.needs_input_grad[1]:
#         saved_a = a
#     ctx.save_for_backward(saved_a, saved_b)


# # This adds training support for the operator. You must provide us
# # the backward formula for the operator and a `setup_context` function
# # to save values to be used in the backward.
# torch.library.register_autograd(
#     "torch_bessel::besselk", _backward, setup_context=_setup_context
# )
