#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cpu/Loops.h>
#include <c10/util/complex.h>
#include <iostream>

#include "bessel_k.h"
#include "iterator.h"

namespace torch_bessel {

at::Tensor modified_bessel_k0_complex_forward_cpu(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_COMPLEX_TYPES(dtype, "modified_bessel_k0_complex_forward_cpu", [&]() {
    at::native::cpu_kernel(iter, [](scalar_t z) -> scalar_t {
      return modified_bessel_k0_complex_forward(z);
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> modified_bessel_k0_complex_forward_backward_cpu(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result1 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_21(result1, result2, z);
  AT_DISPATCH_COMPLEX_TYPES(dtype, "modified_bessel_k0_complex_forward_backward_cpu", [&]() {
    at::native::cpu_kernel_multiple_outputs(iter, [](scalar_t z) -> std::tuple<scalar_t, scalar_t> {
      scalar_t cy[2];
      modified_bessel_k0_complex_forward_backward(z, cy);
      return std::make_tuple(cy[0], cy[1]);
    });
  });
  return std::make_tuple(result1, result2);
}

at::Tensor modified_bessel_k1_complex_forward_cpu(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_COMPLEX_TYPES(dtype, "modified_bessel_k1_complex_forward_cpu", [&]() {
    at::native::cpu_kernel(iter, [](scalar_t z) -> scalar_t {
      return modified_bessel_k1_complex_forward(z);
    });
  });
  return result;
}

// Registers _C as a Python extension module.
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {}

// Defines the operators
TORCH_LIBRARY(torch_bessel, m) {
  m.def("modified_bessel_k0_complex_forward(Tensor z) -> Tensor");
  m.def("modified_bessel_k0_complex_forward_backward(Tensor z) -> (Tensor, Tensor)");
  m.def("modified_bessel_k1_complex_forward(Tensor z) -> Tensor");
}

// Registers CPU implementations for bessel_k
TORCH_LIBRARY_IMPL(torch_bessel, CPU, m) {
  m.impl("modified_bessel_k0_complex_forward", &modified_bessel_k0_complex_forward_cpu);
  m.impl("modified_bessel_k0_complex_forward_backward", &modified_bessel_k0_complex_forward_backward_cpu);
  m.impl("modified_bessel_k1_complex_forward", &modified_bessel_k1_complex_forward_cpu);
}

}
