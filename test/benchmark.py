import argparse
import math
import time

import torch
from scipy import special

import torch_bessel

TIME_SCALES = {"s": 1, "ms": 1000, "us": 1000000}


def besselk(nu, z):
    return special.kv(nu, z)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("example", choices=["py", "cpp"])
    parser.add_argument("-f", "--func", choices=["besselk"], default="besselk")
    parser.add_argument("-d", "--device", choices=["cpu", "cuda"], default="cpu")
    parser.add_argument("-n", type=int, default=1 << 16)
    parser.add_argument("-r", "--runs", type=int, default=100)
    parser.add_argument("--scale", choices=["s", "ms", "us"], default="us")
    parser.add_argument("--double", action="store_true")
    options = parser.parse_args()

    if options.example == "py":
        func = globals()[options.func]
    else:
        func = getattr(torch_bessel.ops, options.func)

    device = torch.device(options.device)
    dtype = torch.float64 if options.double else torch.float32

    kwargs = {"dtype": dtype, "device": device, "requires_grad": False}

    args = (
        0.1 * torch.randn((options.n,), **kwargs),
        0.1 * torch.complex(*torch.randn((2, options.n), **kwargs)),
    )

    forward_min = math.inf
    forward_time = 0
    backward_min = math.inf
    backward_time = 0
    for _ in range(options.runs):
        for t in args:
            if isinstance(t, torch.Tensor):
                t.grad = None

        start = time.time()
        out = func(*args)
        elapsed = time.time() - start
        forward_min = min(forward_min, elapsed)
        forward_time += elapsed

        # start = time.time()
        # out.sum().backward()
        # elapsed = time.time() - start
        # backward_min = min(backward_min, elapsed)
        # backward_time += elapsed

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
