#include "Activation.h"
#define RELU_VAL 0


/**
 *  function that replaces each value that smaller than zero with zero, any
 * other value remains the same
 * @param matrix : the matrix that the relu function will be applied to
 * @return: After applying the relu function, will return new matrix
 */

Matrix activation::relu(const Matrix &matrix)
{
  {
    Matrix relu_result(matrix.get_rows(), matrix.get_cols());
    for (int row = 0; row < matrix.get_rows(); ++row)
    {
      for (int col = 0; col < matrix.get_cols(); ++col)
      {
        if (matrix(row, col) < RELU_VAL)
        {
          relu_result(row, col) = RELU_VAL;
        }
        else
        {
          relu_result(row, col) = matrix(row,col);
        }
      }
    }
    return relu_result;
  }
}

/**
 * A function that calculates the sum of the exponents of all the matrix
 * values, and then multiply that matrix by 1/sum
 * @param matrix : the matrix that the softMax function will be applied to
 * @return: After applying the softmax function, will return new matrix
 */

Matrix activation::softmax(const Matrix &matrix)
{
  float exp_sum = 0;
  int dims = matrix.get_rows() * matrix.get_cols();
  Matrix softmax_result = Matrix(matrix);
  for (int i = 0; i < dims; ++i)
  {
    softmax_result[i] = std::exp (softmax_result[i]);
    exp_sum += softmax_result[i];
  }
  float mult =  (1/exp_sum);
  return mult * softmax_result;
}

