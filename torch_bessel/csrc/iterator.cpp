#include <torch/extension.h>
#include <ATen/TensorIterator.h>


at::TensorIterator build_iterator_11(const at::Tensor& result, const at::Tensor& z) {
  return (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .enforce_safe_casting_to_output(true)
    .add_output(result)
    .add_input(z)
  ).build();
}


at::TensorIterator build_iterator_12(const at::Tensor& result, const at::Tensor& v, const at::Tensor& z) {
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

at::TensorIterator build_iterator_21(const at::Tensor& result1, const at::Tensor& result2, const at::Tensor& z) {
  return (
    at::TensorIteratorConfig()
    .set_check_mem_overlap(true)
    .allow_cpu_scalars(true)
    .enforce_safe_casting_to_output(true)
    .add_output(result1)
    .add_output(result2)
    .add_input(z)
  ).build();
}


at::TensorIterator build_iterator_22(const at::Tensor& result1, const at::Tensor& result2, const at::Tensor& v, const at::Tensor& z) {
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
