/**
 * @file methods/ann/loss_functions/mean_squared_logarithmic_error_impl.hpp
 * @author Saksham Rastogi
 *
 * Implementation of the mean squared logarithmic error function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LOSS_FUNCTION_MEAN_SQUARED_LOGARITHMIC_ERROR_IMPL_HPP
#define MLPACK_METHODS_ANN_LOSS_FUNCTION_MEAN_SQUARED_LOGARITHMIC_ERROR_IMPL_HPP

// In case it hasn't yet been included.
#include "mean_squared_logarithmic_error.hpp"

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

template<typename MatType>
MeanSquaredLogarithmicErrorType<MatType>::MeanSquaredLogarithmicErrorType()
{
  // Nothing to do here.
}

template<typename MatType>
typename MatType::elem_type MeanSquaredLogarithmicErrorType<MatType>::Forward(
    const MatType& prediction,
    const MatType& target)
{
  return arma::accu(arma::square(arma::log(1. + target) -
      arma::log(1. + prediction))) / target.n_cols;
}

template<typename MatType>
void MeanSquaredLogarithmicErrorType<MatType>::Backward(
    const MatType& prediction,
    const MatType& target,
    MatType& loss)
{
  loss = 2 * (arma::log(1. + prediction) - arma::log(1. + target)) /
      ((1. + prediction) * target.n_cols);
}

} // namespace ann
} // namespace mlpack

#endif
