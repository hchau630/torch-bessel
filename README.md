# torch-bessel
PyTorch extension package for Bessel functions with arbitrary real order and complex inputs

# setup
This repo works with PyTorch 2.4+. To setup on Axon with an A40 GPU, I performed the following steps:
1) `ml gcc/10.4` (Axon defaults to a very old version of gcc)
2) `conda create -n torch-bessel python=3.11`
3) `conda env config vars set PYTHONNOUSERSITE=1 -n torch-bessel` (ignore `.local` packages)
4) `conda env config vars set CPATH=/home/hc3190/.conda/envs/torch-bessel/targets/x86_64-linux/include/:$CPATH -n torch-bessel`
5) `conda activate torch-bessel`
6) `conda install nvidia/label/cuda-12.4.1::cuda-toolkit`
7) `pip install -r requirements.txt`

To build and test:
```
rm -r build
pip install .
python test/test_extension.py
```
Note that the first line is only required if you have already built the extension and want to do a fresh rebuild.
