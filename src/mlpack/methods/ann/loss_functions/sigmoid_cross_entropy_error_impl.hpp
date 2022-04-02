/**
 * @file methods/ann/loss_functions/sigmoid_cross_entropy_error_impl.hpp
 * @author Kris Singh
 * @author Shikhar Jaiswal
 *
 * Implementation of the sigmoid cross entropy error performance function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LOSS_FUNCTION_SIGMOID_CROSS_ENTROPY_ERROR_IMPL_HPP
#define MLPACK_METHODS_ANN_LOSS_FUNCTION_SIGMOID_CROSS_ENTROPY_ERROR_IMPL_HPP

// In case it hasn't yet been included.
#include "sigmoid_cross_entropy_error.hpp"
#include <mlpack/methods/ann/activation_functions/softplus_function.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

template<typename MatType>
SigmoidCrossEntropyErrorType<MatType>::SigmoidCrossEntropyErrorType()
{
  // Nothing to do here.
}

template<typename MatType>
inline typename MatType::elem_type
SigmoidCrossEntropyErrorType<MatType>::Forward(
    const MatType& prediction,
    const MatType& target)
{
  typedef typename MatType::elem_type ElemType;
  ElemType maximum = 0;
  for (size_t i = 0; i < prediction.n_elem; ++i)
  {
    maximum += std::max(prediction[i], 0.0) +
        std::log(1 + std::exp(-std::abs(prediction[i])));
  }

  return maximum - arma::accu(prediction % target);
}

template<typename MatType>
inline void SigmoidCrossEntropyErrorType<MatType>::Backward(
    const MatType& prediction,
    const MatType& target,
    MatType& loss)
{
  loss = 1.0 / (1.0 + arma::exp(-prediction)) - target;
}

} // namespace ann
} // namespace mlpack

#endif
