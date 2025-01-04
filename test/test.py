import torch
from scipy import special

import torch_bessel


def main():
    nu, z = torch.tensor(-1.0), torch.tensor(2.0) + 0j
    print(torch_bessel.ops.besselk(nu, z))
    print(special.kv(nu, z))


if __name__ == "__main__":
    main()
