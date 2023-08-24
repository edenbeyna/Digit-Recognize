#include "MlpNetwork.h"

/**
 * Mlp network constructor
 * @param weights : array of weigths matrices
 * @param biases : array of biases matrices
 */
MlpNetwork::MlpNetwork (Matrix weights[], Matrix biases[]) :
    _r1 (Dense (weights[0], biases[0], activation::relu)),
    _r2(Dense (weights[1],biases[1], activation::relu)),
    _r3(Dense (weights[2], biases[2], activation::relu)),
    _r4(Dense (weights[3], biases[3], activation::softmax))
{

}

/**
 * An overload to the () operator, applies the entire network on input
 * mlp network
 * @param input input matrix
 * @return A digit struct
 */

digit MlpNetwork::operator() (const Matrix &input)
{
  float max_prob = 0.0;
  int result_digit = 0;
  Matrix output = Matrix(input);
  output = _r1(output);
  output = _r2(output);
  output = _r3(output);
  output = _r4(output);
  int rows = output.get_rows();
  for(int index = 0; index < rows; index++)
  {
    if(output[index] > max_prob){
      max_prob = output[index];
      result_digit = index;
    }
  }
  digit result;
  result.value = result_digit;
  result.probability = max_prob;
  return result;




}
