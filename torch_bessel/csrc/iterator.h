#pragma once

#include <torch/extension.h>
#include <ATen/TensorIterator.h>


at::TensorIterator build_iterator_11(const at::Tensor& result, const at::Tensor& z);
at::TensorIterator build_iterator_12(const at::Tensor& result, const at::Tensor& v, const at::Tensor& z);
at::TensorIterator build_iterator_21(const at::Tensor& result1, const at::Tensor& result2, const at::Tensor& z);
at::TensorIterator build_iterator_22(const at::Tensor& result1, const at::Tensor& result2, const at::Tensor& v, const at::Tensor& z);

