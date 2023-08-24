#include "Dense.h"

/**
 * Dense constructor
 * @param weights: weight matrix
 * @param bias : bi
 * as vector
 * @param act_func : activation function
 */


Dense::Dense(const Matrix& weights, const Matrix& bias, ActivationFunc
act_func)
{
  _weights = weights;
  _bias = bias;
  _act_func = act_func;
}

Matrix Dense::get_weights() const {
  return _weights;
}

Matrix Dense::get_bias() const {
  return _bias;
}

ActivationFunc Dense::get_activation() const{
  return _act_func;
}

/**
 * An overload to the () operator ,which applies the layer on input and
 * returns output matrix, according to the activation function
 * modifying cell values
 * @param input: input matrix
 * @return : after applying activation func, returns modified matrix
 */

Matrix Dense::operator()(Matrix &input) const{
  Matrix output = _act_func(((_weights * input) + _bias));
  return output;

}