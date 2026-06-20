# About
PyTorch extension package for modified Bessel functions of the second kind with complex inputs.

# Install
Currently only supports Linux and MacOS (Apple silicon, cpu only). To install, simply run
```
pip install torch-bessel -f https://torch-bessel.s3.us-east-2.amazonaws.com/whl/torch-{TORCH}%2B{CUDA}.html
```
where `{TORCH}` should be replaced by either `2.6.0`, `2.7.1`, `2.8.0`, `2.9.1`, `2.10.0`, `2.11.0`, or `2.12.1`, and `{CUDA}` should be replaced by either `cpu`, `cu124`, `cu126`, `cu128`, or `cu130`. The combination of both should match the version of PyTorch installed in your environment. The list of all valid combinations is [here](http://torch-bessel.s3-website.us-east-2.amazonaws.com/whl/). For `cu124` and `cu126`, GPUs with [compute capability](https://developer.nvidia.com/cuda/gpus) (CC) `>=5.0` and `<=9.0` are supported, while for `cu128` and `cu130`, GPUs with CC `>=7.5` are supported. The only combinations which support legacy Linux OSes such as CentOS 7 are `torch==2.6.0+cpu` and `torch==2.6.0+cu124`.

# Example
```
import torch_bessel

real, imag = torch.randn(2, 5, device="cuda")
z = torch.complex(real.abs(), imag)  # correctness for inputs in the left-half complex plane is not gauranteed.
torch_bessel.ops.modified_bessel_k0(z)
```

# Implemented functions
- `modified_bessel_k0`: Same as `torch.special.modified_bessel_k0`, but also handles backpropagation and complex inputs on cpu and cuda. Correctness is guaranteed on the right-half complex plane. On cuda, `torch.chalf` inputs are also supported, though the underlying cuda kernel just upcasts `chalf` to `cfloat` (note that this uses no extra GPU memory, as opposed to manually casting torch.chalf to torch.cfloat before calling `modified_bessel_k0` which doubles the GPU memory used). On the left-half complex plane, function output appears mostly correct, but with small numerical errors for certain inputs. On the negative real line, output is NaN.
- `modified_bessel_k1`: Same as `torch.special.modified_bessel_k1`, but also handles complex inputs on cpu and cuda. Backpropagation not implemented, but this can be easily manually implemented yourself by writing a torch.autograd.Function using the recurrence properties of bessel functions. Same caveats as `modified_bessel_k0` apply.

# Benchmarks
Benchmarking performed with the `asv` package. Results can be viewed at https://hchau630.github.io/torch-bessel.
