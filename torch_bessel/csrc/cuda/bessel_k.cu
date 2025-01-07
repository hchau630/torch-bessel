#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cuda/Loops.cuh>
#include <c10/util/complex.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <thrust/tuple.h>

#include "../bessel_k.h"
#include "../iterator.h"

namespace torch_bessel {

at::Tensor bessel_k0_forward_cuda(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(dtype, "bessel_k0_forward_cuda", [&]() {
    at::native::gpu_kernel(iter, []GPU_LAMBDA(scalar_t z) -> scalar_t {
      return bessel_k0_forward(z);
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> bessel_k0_forward_backward_cuda(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result1 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_21(result1, result2, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(dtype, "bessel_k0_forward_backward_cuda", [&]() {
    at::native::gpu_kernel_multiple_outputs(iter, []GPU_LAMBDA(scalar_t z) -> thrust::tuple<scalar_t, scalar_t> {
      scalar_t cy[2];
      bessel_k0_forward_backward(z, cy);
      return thrust::make_tuple(cy[0], cy[1]);
    });
  });
  return std::make_tuple(result1, result2);
}

// Registers CUDA implementations for bessel_k
TORCH_LIBRARY_IMPL(torch_bessel, CUDA, m) {
  m.impl("bessel_k0_forward", &bessel_k0_forward_cuda);
  m.impl("bessel_k0_forward_backward", &bessel_k0_forward_backward_cuda);
}

}
