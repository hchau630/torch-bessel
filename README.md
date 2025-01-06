# torch-bessel
PyTorch extension package for Bessel functions with arbitrary real order and complex inputs

# building
This repo works with PyTorch 2.4+. To build it on Axon with an A40 GPU, I performed the following steps:
0) `ml gcc/10.4` (Axon defaults to a very old version of gcc)
1) `conda create -n torch-bessel python=3.11`
2) `conda env config vars set PYTHONNOUSERSITE=1 -n torch-bessel` (ignore `.local` packages)
3) `conda env config vars set CPATH=/home/hc3190/.conda/envs/torch-bessel/targets/x86_64-linux/include/:$CPATH`
4) `conda activate torch-bessel`
5) `pip install -r requirements.txt`
6) `pip install .`

To test:
```
python test/test_extension.py
```

