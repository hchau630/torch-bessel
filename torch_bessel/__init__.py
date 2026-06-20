import warnings

# need to import torch before importing torch_bessel._C
import torch
from . import _C, ops

# Silence warning emitted at torch/nested/_internal/nested_tensor.py:417
warnings.filterwarnings(
    "ignore", message="Failed to initialize NumPy: No module named 'numpy'"
)

__all__ = ["ops"]
