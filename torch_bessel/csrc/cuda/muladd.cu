#include <torch/extension.h>
#include <ATen/native/cuda/Loops.cuh>
#include "../cbesk.h"

#include <cuda.h>
#include <cuda_runtime.h>

namespace torch_bessel {

at::Tensor besselk_cpu(const at::Tensor& nu, const at::Tensor& z) {
  TORCH_CHECK(nu.scalar_type() == at::kFloat);
  TORCH_CHECK(z.scalar_type() == at::kComplexFloat);
  TORCH_INTERNAL_ASSERT(nu.device().type() == at::DeviceType::CUDA);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CUDA);
  at::Tensor result = torch::empty(at::IntArrayRef(), at::device(at::kCUDA).dtype(at::kComplexFloat)).resize_(0);
  auto iter = (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .add_output(result)
    .add_input(nu)
    .add_input(z)
  ).build();
  at::native::gpu_kernel(iter, []GPU_LAMBDA(float nu, c10::complex<float> z) -> c10::complex<float> {
      return cbesk(nu, z);
  });
  return result;
}

// Registers CUDA implementations for besselk
TORCH_LIBRARY_IMPL(torch_bessel, CUDA, m) {
  m.impl("besselk", &besselk_cuda);
}

}
