# torch-bessel
PyTorch extension package for Bessel functions with arbitrary real order and complex inputs

# building
This repo works with PyTorch 2.4+. To build it on Axon with an A40 GPU, I performed the following steps:
1) `conda create -n torch-bessel python=3.11`
2) `conda activate torch-bessel`
2) `conda env config vars set PYTHONNOUSERSITE=1` (ignore `.local` packages)
2) `pip install -r requirements.txt`
3) `conda install nvidia/label/cuda-12.4.1::cuda-toolkit`
4) `ml gcc/10.4`
5) `conda env config vars set CPATH=/home/hc3190/.conda/envs/torch-bessel/targets/x86_64-linux/include/:$CPATH`
6) reactivate environment
7) `pip install .`

To test:
```
python test/test_extension.py
```

To compile `test.cpp`:
```
g++ -I "/Users/hoyinchau/opt/anaconda3/envs/torch-bessel/lib/python3.11/site-packages/torch/include" -I "/Users/hoyinchau/opt/anaconda3/envs/torch-bessel/lib/python3.11/site-packages/torch/include/torch/csrc/api/include" -I "/Users/hoyinchau/opt/anaconda3/envs/torch-bessel/include/python3.11" test.cpp torch_bessel/csrc/cbesk/*.cpp -o test.o --std=c++17 libf2c.a -lm
```
