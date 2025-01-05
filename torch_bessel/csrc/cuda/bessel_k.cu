#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cuda/Loops.cuh>
#include <c10/util/complex.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "../bessel.h"
#include "../iterator.h"

namespace torch_bessel {

at::Tensor bessel_k_forward_cuda(const at::Tensor& v, const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(v.device().type() == at::DeviceType::CUDA);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = at::promote_types(v.scalar_type(), z.scalar_type());
  at::Tensor result = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator(result, v, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(iter.common_dtype(), "bessel_k_forward_cuda", [&]() {
    at::native::gpu_kernel(iter, []GPU_LAMBDA(scalar_t v, scalar_t z) -> scalar_t {
        return bessel_k_forward(std::real(v), z);
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> bessel_k_forward_backward_cuda(const at::Tensor& v, const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(v.device().type() == at::DeviceType::CUDA);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = at::promote_types(v.scalar_type(), z.scalar_type());
  at::Tensor result1 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_2(result1, result2, v, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(iter.common_dtype(), "bessel_k_forward_backward_cuda", [&]() {
    at::native::gpu_kernel_multiple_outputs(iter, []GPU_LAMBDA(scalar_t v, scalar_t z) -> std::tuple<scalar_t, scalar_t> {
        return bessel_k_forward_backward(std::real(v), z);
    });
  });
  return std::make_tuple(result1, result2);
}

// Registers CUDA implementations for bessel_k
TORCH_LIBRARY_IMPL(torch_bessel, CUDA, m) {
  m.impl("bessel_k_forward", &bessel_k_forward_cuda);
  m.impl("bessel_k_forward_backward", &bessel_k_forward_backward_cuda);
}

}
