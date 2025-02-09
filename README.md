# About
PyTorch extension package for Bessel functions with arbitrary real order and complex inputs

# Install
Currently only supports Linux (with CUDA 12.4) or MacOS (Apple silicon, cpu only) with python >= 3.9, <= 3.12.
```
pip install torch-bessel
```

# Example
```
import torch_bessel

real, imag = torch.randn(2, 5, device="cuda")
z = torch.complex(real.abs(), imag)  # inputs on the left-half complex plane are set to NaNs.
torch_bessel.ops.modified_bessel_k0(z)
```

# Implemented functions
- `modified_bessel_k0`: Same as `torch.special.modified_bessel_k0`, but also handles backpropagation and complex inputs with $\mathrm{Re}(z) \geq 0$ on cpu and cuda.

# WIP
- `modified_bessel_kv`: Analogue of `scipy.special.kv`.

# Benchmarks
Benchmarking performed with the `asv` package. Results can be viewed at https://hchau630.github.io/torch-bessel.