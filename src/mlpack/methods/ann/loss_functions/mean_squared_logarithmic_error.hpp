/**
 * @file methods/ann/loss_functions/mean_squared_logarithmic_error.hpp
 * @author Saksham Rastogi
 *
 * Definition of the mean squared logarithmic error function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LOSS_FUNCTION_MEAN_SQUARED_LOGARITHMIC_ERROR_HPP
#define MLPACK_METHODS_ANN_LOSS_FUNCTION_MEAN_SQUARED_LOGARITHMIC_ERROR_HPP

#include <mlpack/prereqs.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * The mean squared logarithmic error performance function measures the network's
 * performance according to the mean of squared logarithmic errors.
 *
 * @tparam InputDataType Type of the input data (arma::colvec, arma::mat,
 *         arma::sp_mat or arma::cube).
 * @tparam OutputDataType Type of the output data (arma::colvec, arma::mat,
 *         arma::sp_mat or arma::cube).
 */
template<typename MatType = arma::mat>
class MeanSquaredLogarithmicErrorType
{
 public:
  /**
   * Create the MeanSquaredLogarithmicErrorType object.
   */
  MeanSquaredLogarithmicErrorType();

  /**
   * Computes the mean squared logarithmic error function.
   *
   * @param prediction Predictions used for evaluating the specified loss
   *     function.
   * @param target The target vector.
   */
  typename MatType::elem_type Forward(const MatType& prediction,
                                      const MatType& target);

  /**
   * Ordinary feed backward pass of a neural network.
   *
   * @param prediction Predictions used for evaluating the specified loss
   *     function.
   * @param target The target vector.
   * @param loss The calculated error.
   */
  void Backward(const MatType& prediction,
                const MatType& target,
                MatType& loss);

  /**
   * Serialize the layer
   */
  template<typename Archive>
  void serialize(Archive& ar, const uint32_t /* version */) { }
}; // class MeanSquaredLogarithmicErrorType

typedef MeanSquaredLogarithmicErrorType<arma::mat> MeanSquaredLogarithmicError;

} // namespace ann
} // namespace mlpack

// Include implementation.
#include "mean_squared_logarithmic_error_impl.hpp"

#endif
