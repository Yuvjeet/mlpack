/**
 * @file methods/ann/loss_functions/cosine_embedding_loss_impl.hpp
 * @author Kartik Dutt
 *
 * Implementation of the Cosine Embedding loss function.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_METHODS_ANN_LOSS_FUNCTION_COSINE_EMBEDDING_IMPL_HPP
#define MLPACK_METHODS_ANN_LOSS_FUNCTION_COSINE_EMBEDDING_IMPL_HPP

// In case it hasn't yet been included.
#include "cosine_embedding_loss.hpp"

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

template<typename MatType>
CosineEmbeddingLossType<MatType>::CosineEmbeddingLossType(
    const double margin, const bool similarity, const bool takeMean):
    margin(margin), similarity(similarity), takeMean(takeMean)
{
  // Nothing to do here.
}

template<typename MatType>
typename MatType::elem_type CosineEmbeddingLossType<MatType>::Forward(
    const MatType& prediction,
    const MatType& target)
{
  typedef typename MatType::elem_type ElemType;

  const size_t cols = prediction.n_cols;
  const size_t batchSize = prediction.n_elem / cols;
  if (arma::size(prediction) != arma::size(target))
    Log::Fatal << "Input Tensors must have same dimensions." << std::endl;

  arma::Col<ElemType> inputTemp1 = arma::vectorise(prediction);
  arma::Col<ElemType> inputTemp2 = arma::vectorise(target);
  ElemType loss = 0.0;

  for (size_t i = 0; i < inputTemp1.n_elem; i += cols)
  {
    const ElemType cosDist = kernel::CosineDistance::Evaluate(
        inputTemp1(arma::span(i, i + cols - 1)), inputTemp2(arma::span(i,
        i + cols - 1)));
    if (similarity)
      loss += 1 - cosDist;
    else
    {
      const ElemType currentLoss = cosDist - margin;
      loss += currentLoss > 0 ? currentLoss : 0;
    }
  }

  if (takeMean)
    loss = (ElemType) loss / batchSize;

  return loss;
}

template<typename MatType>
void CosineEmbeddingLossType<MatType>::Backward(
    const MatType& prediction,
    const MatType& target,
    MatType& loss)
{
  typedef typename MatType::elem_type ElemType;

  const size_t cols = prediction.n_cols;
  if (arma::size(prediction) != arma::size(target))
    Log::Fatal << "Input Tensors must have same dimensions." << std::endl;

  arma::Col<ElemType> inputTemp1 = arma::vectorise(prediction);
  arma::Col<ElemType> inputTemp2 = arma::vectorise(target);
  loss.set_size(arma::size(inputTemp1));

  arma::Col<ElemType> outputTemp(loss.memptr(), inputTemp1.n_elem,
      false, false);
  for (size_t i = 0; i < inputTemp1.n_elem; i += cols)
  {
    const ElemType cosDist = kernel::CosineDistance::Evaluate(inputTemp1(
        arma::span(i, i + cols -1)), inputTemp2(arma::span(i, i + cols -1)));

    if (cosDist < margin && !similarity)
      outputTemp(arma::span(i, i + cols - 1)).zeros();
    else
    {
      const int multiplier = similarity ? 1 : -1;
      outputTemp(arma::span(i, i + cols -1)) = -1 * multiplier *
          (arma::normalise(inputTemp2(arma::span(i, i + cols - 1))) -
          cosDist * arma::normalise(inputTemp1(arma::span(i, i + cols -
          1)))) / std::sqrt(arma::accu(arma::pow(inputTemp1(arma::span(i, i +
          cols - 1)), 2)));
    }
  }
}

template<typename MatType>
template<typename Archive>
void CosineEmbeddingLossType<MatType>::serialize(
    Archive& ar, const uint32_t /* version */)
{
  ar(CEREAL_NVP(margin));
  ar(CEREAL_NVP(similarity));
  ar(CEREAL_NVP(takeMean));
}

} // namespace ann
} // namespace mlpack

#endif
