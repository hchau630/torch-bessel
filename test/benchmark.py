import argparse
import math
import time

import torch
from scipy import special

import torch_bessel

TIME_SCALES = {"s": 1, "ms": 1000, "us": 1000000}


def bessel_k0(z):
    return special.kv(0.0, z)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("example", choices=["py", "cpp"])
    parser.add_argument("-f", "--func", choices=["bessel_k0"], default="bessel_k0")
    parser.add_argument("-d", "--device", choices=["cpu", "cuda"], default="cpu")
    parser.add_argument("-n", type=int, default=1 << 16)
    parser.add_argument("-r", "--runs", type=int, default=100)
    parser.add_argument("-s", "--scale", choices=["s", "ms", "us"], default="us")
    parser.add_argument("-b", "--backward", action="store_true")
    parser.add_argument("--double", action="store_true")
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
