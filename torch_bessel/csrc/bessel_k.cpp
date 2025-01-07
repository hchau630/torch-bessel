#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cpu/Loops.h>
#include <c10/util/complex.h>
#include <iostream>

#include "bessel_k.h"
#include "bessel_k0.h"
#include "iterator.h"

namespace torch_bessel {

at::Tensor bessel_k_forward_cpu(const at::Tensor& v, const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(v.device().type() == at::DeviceType::CPU);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = at::promote_types(v.scalar_type(), z.scalar_type());
  at::Tensor result = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_12(result, v, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(iter.common_dtype(), "bessel_k_forward_cpu", [&]() {
    at::native::cpu_kernel(iter, [](scalar_t v, scalar_t z) -> scalar_t {
      return bessel_k_forward(std::real(v), z);
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> bessel_k_forward_backward_cpu(const at::Tensor& v, const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(v.device().type() == at::DeviceType::CPU);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = at::promote_types(v.scalar_type(), z.scalar_type());
  at::Tensor result1 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_22(result1, result2, v, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(iter.common_dtype(), "bessel_k_forward_backward_cpu", [&]() {
    at::native::cpu_kernel_multiple_outputs(iter, [](scalar_t v, scalar_t z) -> std::tuple<scalar_t, scalar_t> {
      return bessel_k_forward_backward(std::real(v), z);
    });
  });
  return std::make_tuple(result1, result2);
}

at::Tensor bessel_k0_forward_cpu(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_11(result, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(dtype, "bessel_k0_forward_cpu", [&]() {
    at::native::cpu_kernel(iter, [](scalar_t z) -> scalar_t {
      return bessel_k0_forward(z);
    });
  });
  return result;
}

std::tuple<at::Tensor, at::Tensor> bessel_k0_forward_backward_cpu(const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = z.scalar_type();
  at::Tensor result1 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::Tensor result2 = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator_21(result1, result2, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(dtype, "bessel_k0_forward_backward_cpu", [&]() {
    at::native::cpu_kernel_multiple_outputs(iter, [](scalar_t z) -> std::tuple<scalar_t, scalar_t> {
      scalar_t cy[2];
      bessel_k0_forward_backward(z, cy);
      return std::make_tuple(cy[0], cy[1]);
    });
  });
  return std::make_tuple(result1, result2);
}


// Registers _C as a Python extension module.
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {}

// Defines the operators
TORCH_LIBRARY(torch_bessel, m) {
  m.def("bessel_k_forward(Tensor nu, Tensor z) -> Tensor");
  m.def("bessel_k_forward_backward(Tensor nu, Tensor z) -> (Tensor, Tensor)");
  m.def("bessel_k0_forward(Tensor z) -> Tensor");
  m.def("bessel_k0_forward_backward(Tensor z) -> (Tensor, Tensor)");
}

// Registers CPU implementations for bessel_k
TORCH_LIBRARY_IMPL(torch_bessel, CPU, m) {
  m.impl("bessel_k_forward", &bessel_k_forward_cpu);
  m.impl("bessel_k_forward_backward", &bessel_k_forward_backward_cpu);
  m.impl("bessel_k0_forward", &bessel_k0_forward_cpu);
  m.impl("bessel_k0_forward_backward", &bessel_k0_forward_backward_cpu);
}

}
