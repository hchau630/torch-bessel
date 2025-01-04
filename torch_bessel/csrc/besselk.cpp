#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cpu/Loops.h>
#include <c10/util/complex.h>
#include "cbesk_hi.h"

#include <vector>

namespace torch_bessel {

at::Tensor besselk_cpu(const at::Tensor& nu, const at::Tensor& z) {
  // std::cout << "nu.scalar_type(): " << nu.scalar_type() << std::endl;
  // std::cout << "z.scalar_type(): " << z.scalar_type() << std::endl;
  TORCH_CHECK(nu.scalar_type() == at::kFloat);
  TORCH_CHECK(z.scalar_type() == at::kComplexFloat);
  // std::cout << "hi" << std::endl;
  TORCH_INTERNAL_ASSERT(nu.device().type() == at::DeviceType::CPU);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::Tensor result = torch::empty(at::IntArrayRef(), at::kComplexFloat).resize_(0);
  // std::cout << "hihi" << std::endl;
  auto iter = (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .promote_inputs_to_common_dtype(true)
    .cast_common_dtype_to_outputs(true)
    .enforce_safe_casting_to_output(true)
    .promote_integer_inputs_to_float(true)
    .add_output(result)
    .add_input(nu)
    .add_input(z)
  ).build();
  at::native::cpu_kernel(iter, [](c10::complex<float> nu, c10::complex<float> z) -> c10::complex<float> {
      return cbesk_hihi(nu.real(), z);
  });
  // std::cout << "hihihi" << std::endl;
  return result;
}

// Registers _C as a Python extension module.
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {}

// Defines the operators
TORCH_LIBRARY(torch_bessel, m) {
  m.def("besselk(Tensor nu, Tensor z) -> Tensor");
}

// Registers CPU implementations for besselk
TORCH_LIBRARY_IMPL(torch_bessel, CPU, m) {
  m.impl("besselk", &besselk_cpu);
}

}
