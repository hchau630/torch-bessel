import argparse
import math
import time

import torch
from torch import Tensor
from scipy import special

import torch_bessel

TIME_SCALES = {"s": 1, "ms": 1000, "us": 1000000}


class ModifiedBesselK0(torch.autograd.Function):
    @staticmethod
    def forward(z):
        if z.is_complex():
            out = special.kv(0, z.detach().cpu().numpy())
            out = torch.as_tensor(out).to(dtype=z.dtype, device=z.device)
        else:
            out = torch.special.modified_bessel_k0(z)
        return out

    @staticmethod
    def setup_context(ctx, inputs, _):
        if ctx.needs_input_grad[0]:
            ctx.save_for_backward(*inputs)
        ctx.set_materialize_grads(False)

    @staticmethod
    def backward(ctx, grad_output):
        if grad_output is None or not ctx.needs_input_grad[0]:
            return None

        (z,) = ctx.saved_tensors
        if z.is_complex():
            # Note: We need to take the conjugate of the derivative. To understand why,
            # see https://pytorch.org/docs/stable/notes/autograd.html#complex-autograd-doc
            # where in equation 4 we note that since this is a holomorphic function,
            # the derivative w.r.t conjugate of z is zero, so the first term is zero.
            grad = -special.kv(1, z.detach().cpu().numpy())
            grad = torch.as_tensor(grad).to(dtype=z.dtype, device=z.device).conj()
        else:
            grad = -torch.special.modified_bessel_k1(z)

        return grad.mul_(grad_output)


def modified_bessel_k0(z: Tensor):
    return ModifiedBesselK0.apply(z)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("example", choices=["py", "cpp"])
    parser.add_argument(
        "-f", "--func", choices=["modified_bessel_k0"], default="modified_bessel_k0"
    )
    parser.add_argument("-d", "--device", choices=["cpu", "cuda"], default="cpu")
    parser.add_argument("-n", type=int, default=1 << 16)
    parser.add_argument("-r", "--runs", type=int, default=100)
    parser.add_argument("-s", "--scale", choices=["s", "ms", "us"], default="us")
    parser.add_argument("-b", "--backward", action="store_true")
    parser.add_argument("--double", action="store_true")
    parser.add_argument("--real", action="store_true")
    options = parser.parse_args()

    if options.example == "py":
        func = globals()[options.func]
    else:
        func = getattr(torch_bessel.ops, options.func)

    device = torch.device(options.device)
    dtype = torch.float64 if options.double else torch.float32

    kwargs = {"dtype": dtype, "device": device}

    forward_min = math.inf
    forward_time = 0
    backward_min = math.inf
    backward_time = 0
    for _ in range(options.runs):
        real = torch.randn(options.n, **kwargs, requires_grad=options.backward).abs()
        if options.real:
            args = (real,)
        else:
            imag = torch.randn(options.n, **kwargs, requires_grad=options.backward)
            args = (torch.complex(real, imag),)

        if options.device == "cuda":
            torch.cuda.synchronize()
        start = time.time()
        out = func(*args)
        if options.device == "cuda":
            torch.cuda.synchronize()
        elapsed = time.time() - start
        forward_min = min(forward_min, elapsed)
        forward_time += elapsed

        if options.backward:
            out = out.norm()
            if options.device == "cuda":
                torch.cuda.synchronize()
            start = time.time()
            out.backward()
            if options.device == "cuda":
                torch.cuda.synchronize()
            elapsed = time.time() - start
            backward_min = min(backward_min, elapsed)
            backward_time += elapsed

    scale = TIME_SCALES[options.scale]
    forward_min *= scale
    backward_min *= scale
    forward_average = forward_time / options.runs * scale
    backward_average = backward_time / options.runs * scale

    print(
        "Forward: {0:.3f}/{1:.3f} {4} | Backward {2:.3f}/{3:.3f} {4}".format(
            forward_min, forward_average, backward_min, backward_average, options.scale
        )
    )


if __name__ == "__main__":
    main()
