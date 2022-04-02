/**
 * @file methods/ann/loss_functions/reconstruction_loss_impl.hpp
 * @author Atharva Khandait
 *
 * Implementation of the reconstruction loss performance function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LOSS_FUNCTION_RECONSTRUCTION_LOSS_IMPL_HPP
#define MLPACK_METHODS_ANN_LOSS_FUNCTION_RECONSTRUCTION_LOSS_IMPL_HPP

// In case it hasn't yet been included.
#include "reconstruction_loss.hpp"

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

template<typename MatType, typename DistType>
ReconstructionLossType<MatType, DistType>::ReconstructionLossType()
{
  // Nothing to do here.
}

template<typename MatType, typename DistType>
typename MatType::elem_type ReconstructionLossType<MatType, DistType>::Forward(
    const MatType& prediction, const MatType& target)
{
  dist = DistType(prediction);
  return -dist.LogProbability(target);
}

template<typename MatType, typename DistType>
void ReconstructionLossType<MatType, DistType>::Backward(
    const MatType& /* prediction */,
    const MatType& target,
    MatType& loss)
{
  dist.LogProbBackward(target, loss);
  loss *= -1;
}

template<typename MatType, typename DistType>
template<typename Archive>
void ReconstructionLossType<MatType, DistType>::serialize(
    Archive& ar,
    const uint32_t /* version */)
{
  ar(dist);
}

} // namespace ann
} // namespace mlpack

#endif
