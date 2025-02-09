import torch
from asv_runner.benchmarks.mark import skip_benchmark_if

import torch_bessel


def _setup(n, is_real, dtype=torch.float, requires_grad=False, device="cpu"):
    kwargs = {"dtype": dtype, "requires_grad": requires_grad, "device": device}
    real = torch.randn(n, **kwargs).abs()
    if is_real:
        args = (real,)
    else:
        imag = torch.randn(n, **kwargs)
        args = (torch.complex(real, imag),)
    return args


class ModifiedBesselK0ForwardCPU:
    params = (
        [10_000, 100_000, 1_000_000],
        [False, True],
        [torch.float32, torch.float64],
        [False, True],
    )
    param_names = ["n", "is_real", "dtype", "requires_grad"]

    def setup(self, n, is_real, dtype, requires_grad):
        self.args = _setup(n, is_real, dtype, requires_grad)

    def time_modified_bessel_k0_forward_cpu(self, n, is_real, dtype, requires_grad):
        torch_bessel.ops.modified_bessel_k0(*self.args)


@skip_benchmark_if(not torch.cuda.is_available())
class ModifiedBesselK0ForwardCUDA:
    params = (
        [10_000, 100_000, 1_000_000],
        [False, True],
        [torch.float32, torch.float64],
        [False, True],
    )
    param_names = ["n", "is_real", "dtype", "requires_grad"]

    def setup(self, n, is_real, dtype, requires_grad):
        self.args = _setup(n, is_real, dtype, requires_grad, device="cuda")

    def time_modified_bessel_k0_forward_cuda(self, n, is_real, dtype, requires_grad):
        torch.cuda.synchronize()
        torch_bessel.ops.modified_bessel_k0(*self.args)
        torch.cuda.synchronize()


class ModifiedBesselK0BackwardCPU:
    warmup_time = 0.0  # for some reason backward is called multiple times if not 0
    number = 1  # Avoids calling backward multiple times
    params = (
        [10_000, 100_000, 1_000_000],
        [False, True],
        [torch.float32, torch.float64],
    )
    param_names = ["n", "is_real", "dtype"]

    def setup(self, n, is_real, dtype):
        args = _setup(n, is_real, dtype, requires_grad=True)
        self.out = torch_bessel.ops.modified_bessel_k0(*args).norm()

    def time_modified_bessel_k0_backward_cpu(self, n, is_real, dtype):
        self.out.backward()


@skip_benchmark_if(not torch.cuda.is_available())
class ModifiedBesselK0BackwardCUDA:
    warmup_time = 0.0  # for some reason backward is called multiple times if not 0
    number = 1  # Avoids calling backward multiple times
    params = (
        [10_000, 100_000, 1_000_000],
        [False, True],
        [torch.float32, torch.float64],
    )
    param_names = ["n", "is_real", "dtype"]

    def setup(self, n, is_real, dtype):
        args = _setup(n, is_real, dtype, requires_grad=True, device="cuda")
        self.out = torch_bessel.ops.modified_bessel_k0(*args).norm()

    def time_modified_bessel_k0_backward_cuda(self, n, is_real, dtype):
        torch.cuda.synchronize()
        self.out.backward()
        torch.cuda.synchronize()
