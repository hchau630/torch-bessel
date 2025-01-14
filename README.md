# About
PyTorch extension package for Bessel functions with arbitrary real order and complex inputs

# Install
```
pip install torch-bessel
```

# Example usage
```
import torch_bessel

z = torch.randn(10) + 1j
torch_bessel.ops.modified_bessel_k0(z)
```

# Implemented functions
- `modified_bessel_k0`: Same as `torch.special.modified_bessel_k0`, but also handles backpropagation and complex inputs with $\mathrm{Im}(z) \geq 0$ on cpu and cuda.

# WIP
- `modified_bessel_kv`: Analogue of `scipy.special.kv`.