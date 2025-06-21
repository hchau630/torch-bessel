#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cuda/Loops.cuh>
#include <ATen/OpMathType.h>
#include <c10/util/complex.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <thrust/tuple.h>

#include "../bessel_k.h"
#include "../iterator.h"

namespace torch_bessel {

at::Tensor modified_bessel_k0_complex_forward_cuda(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_COMPLEX_TYPES_AND(at::kComplexHalf, dtype, "modified_bessel_k0_complex_forward_cuda", [&]() {
    at::native::gpu_kernel(iter, []GPU_LAMBDA(scalar_t z) -> scalar_t {
      using opmath_t = at::opmath_type<scalar_t>;
      return modified_bessel_k0_complex_forward(static_cast<opmath_t>(z));
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> modified_bessel_k0_complex_forward_backward_cuda(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result1 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_21(result1, result2, z);
  AT_DISPATCH_COMPLEX_TYPES_AND(at::kComplexHalf, dtype, "modified_bessel_k0_complex_forward_backward_cuda", [&]() {
    at::native::gpu_kernel_multiple_outputs(iter, []GPU_LAMBDA(scalar_t z) -> thrust::tuple<scalar_t, scalar_t> {
      using opmath_t = at::opmath_type<scalar_t>;
      opmath_t cy[2];
      modified_bessel_k0_complex_forward_backward(static_cast<opmath_t>(z), cy);
      return thrust::make_tuple(cy[0], cy[1]);
    });
  });
  return std::make_tuple(result1, result2);
}

at::Tensor modified_bessel_k1_complex_forward_cuda(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(dtype)).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_COMPLEX_TYPES_AND(at::kComplexHalf, dtype, "modified_bessel_k1_complex_forward_cuda", [&]() {
    at::native::gpu_kernel(iter, []GPU_LAMBDA(scalar_t z) -> scalar_t {
      using opmath_t = at::opmath_type<scalar_t>;
      return modified_bessel_k1_complex_forward(static_cast<opmath_t>(z));
    });
  });
  return result;
}

// Registers CUDA implementations for bessel_k
TORCH_LIBRARY_IMPL(torch_bessel, CUDA, m) {
  m.impl("modified_bessel_k0_complex_forward", &modified_bessel_k0_complex_forward_cuda);
  m.impl("modified_bessel_k0_complex_forward_backward", &modified_bessel_k0_complex_forward_backward_cuda);
  m.impl("modified_bessel_k1_complex_forward", &modified_bessel_k1_complex_forward_cuda);
}

}
