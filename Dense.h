#ifndef DENSE_H
#define DENSE_H
#include "Activation.h"

class Dense
{
 private:
  Matrix _weights;
  Matrix _bias;
  ActivationFunc _act_func;

 public:
  Dense(const Matrix &weights, const Matrix &bias, ActivationFunc act_func);
  Matrix get_weights() const;
  Matrix get_bias() const;
  ActivationFunc get_activation() const;
  Matrix operator()(Matrix &input) const;
};


#endif //DENSE_H
