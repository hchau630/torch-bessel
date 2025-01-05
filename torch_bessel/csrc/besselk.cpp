#include <torch/extension.h>
#include <ATen/TensorIterator.h>
#include <ATen/native/cpu/Loops.h>
#include <c10/util/complex.h>
#include "bessel.h"

#include <vector>

namespace torch_bessel {

at::TensorIterator build_iterator(const at::Tensor& result, const at::Tensor& v, const at::Tensor& z) {
  return (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .promote_inputs_to_common_dtype(true)
    .cast_common_dtype_to_outputs(true)
    .enforce_safe_casting_to_output(true)
    .promote_integer_inputs_to_float(true)
    .add_output(result)
    .add_input(v)
    .add_input(z)
  ).build();
}

at::TensorIterator build_iterator_2(const at::Tensor& result1, const at::Tensor& result2, const at::Tensor& v, const at::Tensor& z) {
  return (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .promote_inputs_to_common_dtype(true)
    .cast_common_dtype_to_outputs(true)
    .enforce_safe_casting_to_output(true)
    .promote_integer_inputs_to_float(true)
    .add_output(result1)
    .add_output(result2)
    .add_input(v)
    .add_input(z)
  ).build();
}

at::Tensor bessel_k_forward_cpu(const at::Tensor& v, const at::Tensor& z) {
  TORCH_INTERNAL_ASSERT(v.device().type() == at::DeviceType::CPU);
  TORCH_INTERNAL_ASSERT(z.device().type() == at::DeviceType::CPU);
  at::ScalarType dtype = at::promote_types(v.scalar_type(), z.scalar_type());
  at::Tensor result = torch::empty(at::IntArrayRef(), dtype).resize_(0);
  at::TensorIterator iter = build_iterator(result, v, z);
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
  at::TensorIterator iter = build_iterator_2(result1, result2, v, z);
  AT_DISPATCH_FLOATING_AND_COMPLEX_TYPES(iter.common_dtype(), "bessel_k_forward_backward_cpu", [&]() {
    at::native::cpu_kernel_multiple_outputs(iter, [](scalar_t v, scalar_t z) -> std::tuple<scalar_t, scalar_t> {
        return bessel_k_forward_backward(std::real(v), z);
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
}

// Registers CPU implementations for besselk
TORCH_LIBRARY_IMPL(torch_bessel, CPU, m) {
  m.impl("bessel_k_forward", &bessel_k_forward_cpu);
  m.impl("bessel_k_forward_backward", &bessel_k_forward_backward_cpu);
}

}
