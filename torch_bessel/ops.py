from pathlib import Path
from numbers import Number
from typing import Union

import torch
from torch import Tensor

__all__ = ["modified_bessel_k0", "modified_bessel_k1"]

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
    def forward(z, singularity):
        if not z.is_complex():
            out = (torch.special.modified_bessel_k0(z), None)
        elif not z.requires_grad:
            out = (
                torch.ops.torch_bessel.modified_bessel_k0_complex_forward.default(z),
                None,
            )
        else:
            out = torch.ops.torch_bessel.modified_bessel_k0_complex_forward_backward.default(
                z
            )

        if singularity is None:
            return (*out, None)

        mask = z != 0
        return (out[0].where(mask, singularity), out[1], mask)

    @staticmethod
    def setup_context(ctx, inputs, outputs):
        if ctx.needs_input_grad[1]:
            raise NotImplementedError("Gradient w.r.t. singularity is not implemented")

        if ctx.needs_input_grad[0]:
            if outputs[1] is None:
                ctx.save_for_backward(inputs[0], None, outputs[2])
            else:
                ctx.save_for_backward(None, outputs[1], outputs[2])

        ctx.set_materialize_grads(False)

    @staticmethod
    def backward(ctx, grad, _, __):
        if grad is None or not ctx.needs_input_grad[0]:
            return (None, None)

        x, deriv, mask = ctx.saved_tensors
        if deriv is None:
            out = -torch.special.modified_bessel_k1(x).mul_(grad)
        else:
            out = grad * deriv
        if mask is not None:
            out = out.where(mask, 0)
        return (out, None)

    @staticmethod
    def vmap(info, in_dims, z, singularity):
        if singularity is None and in_dims[1] is not None:
            raise ValueError("in_dims[1] must be None if singularity is not provided.")

        if in_dims[0] is not None:
            z = z.movedim(in_dims[0], 0)

        if in_dims[1] is not None:
            singularity = singularity.movedim(in_dims[1], 0)

        out = ModifiedBesselK0.apply(z, singularity)
        out_dims = [0] * 3 if any(d is not None for d in in_dims) else [None] * 3
        if out[1] is None:
            out_dims[1] = None
        if out[2] is None:
            out_dims[2] = None

        return (out, tuple(out_dims))


def modified_bessel_k0(
    z: Tensor, singularity: Union[Number, Tensor, None] = None
) -> Tensor:
    return ModifiedBesselK0.apply(z, singularity)[0]


def modified_bessel_k1(z: Tensor) -> Tensor:
    # non-differentiable for now
    if not z.is_complex():
        return torch.special.modified_bessel_k1(z)
    return torch.ops.torch_bessel.modified_bessel_k1_complex_forward.default(z)


@torch.library.register_fake("torch_bessel::modified_bessel_k0_complex_forward")
def _(z):
    return torch.empty_like(z)


@torch.library.register_fake(
    "torch_bessel::modified_bessel_k0_complex_forward_backward"
)
def _(z):
    return torch.empty_like(z), torch.empty_like(z)


@torch.library.register_fake("torch_bessel::modified_bessel_k1_complex_forward")
def _(z):
    return torch.empty_like(z)


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
