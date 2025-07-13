# About
PyTorch extension package for modified Bessel functions of the second kind with complex inputs

# Install
Currently only supports Linux (with CUDA 12.4) or MacOS (Apple silicon, cpu only) with python >= 3.9, <= 3.12.
```
pip install torch-bessel
```

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

# WIP
- `modified_bessel_kv`: Analogue of `scipy.special.kv`.

# Benchmarks
Benchmarking performed with the `asv` package. Results can be viewed at https://hchau630.github.io/torch-bessel.
