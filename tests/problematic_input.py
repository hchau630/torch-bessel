import torch
import torch_bessel

from scipy import special

z = torch.linspace(0.5, 1.5, 20) * torch.tensor(70.1162 + 89.0190j)
print(torch_bessel.ops.modified_bessel_k0(z))
print(special.kv(0.0, z.detach().cpu()))
