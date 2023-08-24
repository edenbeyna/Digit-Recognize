#include <iostream>
#include <stdexcept>
#include "Matrix.h"
#define MIN_MATRIX_IND 1
#define DEFAULT_VALUE 0
#define OUT_OF_RANGE1 "illegal matrix size"
#define OUT_OF_RANGE2 "requested index is out of range"
#define LENGTH_ERROR1 "matrices of different dimensions,cannot multiply"
#define LENGTH_ERROR2 "matrices of different dimensions,cannot add"
#define FILE_ERROR "unable to complete reading from file"
#define MIN_PROB 0.1



using std::cout;
using std::endl;

/**
 * Matrix constructor, conctructs matrix with given dimensions and a
 * default value (0) for each slot
 * @param rows : matrix # of rows
 * @param cols : matrix # of cols
 */

Matrix::Matrix (int rows, int cols) :
    _matrix_dims{rows = rows, cols = cols}
{ if(rows < 1 || cols < 1){
  throw std::out_of_range(OUT_OF_RANGE1);
}
  int size = rows*cols;
  _data = new float[size];
  for (int i = 0; i < size ; i++)
  {
    _data[i] = DEFAULT_VALUE;
  }
}

/**
 * A default constructor of the matrix
 *  constructs 1 X 1 matrix with default zero value
 */

Matrix::Matrix () :
Matrix(MIN_MATRIX_IND, MIN_MATRIX_IND){
  _data = new float[MIN_MATRIX_IND];
  _data[DEFAULT_VALUE] = DEFAULT_VALUE;
}

/**
 * A copy constructor.
 * @param matrix: the matrix to be copied
 */


Matrix::Matrix (const Matrix &matrix) :
    _matrix_dims {matrix._matrix_dims.rows, matrix._matrix_dims.cols}
    {
      int size = matrix._matrix_dims.rows * matrix._matrix_dims.cols;
      _data = new float[size];
      int ind = 0;
      while(ind < size)
      {
        _data[ind] = matrix._data[ind];
        ++ind;
      }
}

/**
 * A destructor, deletes the matrix
 */

Matrix::~Matrix ()
{
  delete[](_data);
}


int Matrix::get_rows () const
{
  return _matrix_dims.rows;
}

int Matrix::get_cols() const
{
  return _matrix_dims.cols;
}

/**
 * A function that transforms the matrix into a vector
 * @return a 1 X (matrix rows * matrix cols) vector
 */

Matrix Matrix::vectorize ()
{
  _matrix_dims.rows = _matrix_dims.rows * _matrix_dims.cols;
  _matrix_dims.cols = 1;
  Matrix vector = *this;
  return vector;
}

void Matrix::plain_print () const
{
  for(int row = 0; row < _matrix_dims.rows; ++row){
    for(int col = 0; col < _matrix_dims.cols; ++col){
      cout << (*this)(row, col) << " ";

    }
    cout << endl;
  }
}

/**
 * A function return the index of the largest element in the matrix.
*/

int Matrix::argmax() const{
  int index = 0;
  float max = _data[0];

  for (int i = 1; i < _matrix_dims.rows * _matrix_dims.cols; i++) {
    if (_data[i] > max) {
      max = _data[i];
      index = i;
    }
  }
  return index;
}
/**
 *  function return a matrix that is the Hadmard product of out matrix and
 * another matrix
 * @param other the matrix with want to multipy its elements with out matrix
 * elements
 * @return the elementwise multiplication product
 */
Matrix Matrix::dot(const Matrix &other)
{
  if(_matrix_dims.rows != other._matrix_dims.rows || _matrix_dims.cols !=
                                                     other._matrix_dims.cols){
    throw std::length_error(LENGTH_ERROR1);
  }
  Matrix result = *this;
  int size = _matrix_dims.rows * _matrix_dims.cols;
  for(int ind = 0; ind < size; ++ind){
    result._data[ind] *= other._data[ind];
  }
  return result;
}

/**
 * assigment operator, puts given matrix values into the current matrix
 * @param other: matrix who's value we want to assign
 * @return: current matrix with the given matrix values
 */

Matrix& Matrix::operator=(const Matrix &other){
  if(this == &other){
    return *this;
  }
  int new_size = other._matrix_dims.cols * other._matrix_dims.rows;
  delete[] _data;
  _matrix_dims = other._matrix_dims;
  _data = new float[new_size];
  for(int ind = 0; ind < new_size; ++ind){
    _data[ind] = other._data[ind];
  }
  return *this;
}

/**
 * An overload to the multiplication operator
 * @param other : a matrix that will be multiplied by our matrix
 * @return a matrix the is the multiplication result of the two matrices
 */

Matrix Matrix::operator* (const Matrix &other) const
{
  if((_matrix_dims.cols != other._matrix_dims.rows)){
    throw std::length_error(LENGTH_ERROR1);
  }
  int new_rows = _matrix_dims.rows;
  int new_cols = other._matrix_dims.cols;
  Matrix mult_result = Matrix(new_rows, new_cols);
  for(int i = 0 ; i < _matrix_dims.rows; ++i){
    for(int j = 0; j<other._matrix_dims.cols; ++j){
      for(int d = 0; d<other._matrix_dims.rows; ++d){
        mult_result(i, j) += (*this)(i,d) * other(d, j);
      }
    }
  }
  return mult_result;
}

/**
 * An overload to the multiplication operator, multiplies our matrix by a
 * scalar on the right
 * @param right_scalar : the scalar we want to multiply out matrix with
 * @return : a matrix that is the result of this multiplication
 */

Matrix Matrix::operator* (const float &right_scalar) const
{
  Matrix new_matrix = *this;
  int size = _matrix_dims.rows * _matrix_dims.cols;
  for(int ind = 0; ind < size; ++ind){
    new_matrix._data[ind] *= right_scalar;
  }
  return new_matrix;
}

/**
 * An overload to the multiplication operator, multiplies our matrix by a
 * scalar on the left
 * @param right_scalar : the scalar we want to multiply out matrix with
 * @return : a matrix that is the result of this multiplication
 */


Matrix operator*(const float &left_scalar, const Matrix &other){
  Matrix new_matrix = other;
  int size = other._matrix_dims.rows * other._matrix_dims.cols;
  for(int ind = 0; ind < size; ++ind){
    new_matrix._data[ind] *= left_scalar;
  }
  return new_matrix;
}

/**
 * An overload to the addition operator, adds two matrices
 * @param other: the matrix we want to add to out matrix
 * @return: a matrix that is the result of this addition
 */

Matrix Matrix::operator+ (const Matrix &other) const
{
  if(_matrix_dims.rows != other._matrix_dims.rows || _matrix_dims.cols !=
  other._matrix_dims.cols){
    throw std::length_error(LENGTH_ERROR2);
  }
  Matrix add_result = *this;
  for(int row = 0; row<_matrix_dims.rows; ++row){
    for(int col = 0; col< _matrix_dims.cols; ++col){
      add_result(row,col) += other(row,col);
    }
  }
  return add_result;
}

/**
* An overload to the += operator , adds values of another matrix to our matrix
* @param other the other matrix we want to add to our matrix
* @return current matrix, after adding values of the other matrix to our
 * matrix values
*/


Matrix& Matrix::operator+= (const Matrix &other)
{
  if(_matrix_dims.rows != other._matrix_dims.rows || _matrix_dims.cols !=
                                                     other._matrix_dims.cols){
    throw std::length_error(LENGTH_ERROR2);
  }
  for(int row = 0; row<_matrix_dims.rows; ++row){
    for(int col = 0; col< _matrix_dims.cols; ++col){
      (*this)(row,col) += other(row,col);
    }
  }
  return *this;
}

/**
 * An overload to the () operator , returns the (i,j) element of the current
 * matrix
 * @param i: given row
 * @param j: given column
 * @return  the (i, j) element of our matrix
 */

float& Matrix::operator() (const int &i, const int &j)
{
  if((_matrix_dims.rows <= i)|| (_matrix_dims.cols <= j)){
    throw std::out_of_range(OUT_OF_RANGE2);
  }
  int index = _matrix_dims.cols * i + j;
  return _data[index];
}

/**
 * A const overload to the () operator , returns the (i,j) element of the
 * current matrix
 * @param i: given row
 * @param j: given column
 * @return  the (i, j) element of our matrix
 */

float Matrix::operator() (const int &i, const int &j) const
{
  if((_matrix_dims.rows <= i)|| (_matrix_dims.cols <= j)){
    throw std::out_of_range(OUT_OF_RANGE2);
  }
  else if(i < 0 || j < 0){
    throw std::out_of_range(OUT_OF_RANGE2);
  }
  int index = _matrix_dims.cols * i + j;
  return _data[index];
}

/**
 * A function that transforms our matrix into its transpose matrix
 * another matrix
 * @return current matrix in its transpose state
 */


Matrix& Matrix::transpose ()
{
  int temp_rows = _matrix_dims.rows;
  int temp_cols = _matrix_dims.cols;
  int size = _matrix_dims.rows * _matrix_dims.cols;
  float * new_data = new float [size];
  for (int row = 0; row < _matrix_dims.rows; ++row){
    for(int col = 0; col< _matrix_dims.cols; ++col){
      new_data[col * _matrix_dims.rows + row ] = (*this)(row, col);
    }

  }
  _data = new_data;
  _matrix_dims.rows = temp_cols;
  _matrix_dims.cols = temp_rows;
  return *this;
}

/**
 * A function that calculates the norm of our matrix
 * another matrix
 * @return the norm of our matrix
 */


float Matrix::norm () const
{
  float norm = 0;
  for (int row = 0; row < _matrix_dims.rows; ++row)
  {
    for (int col = 0; col < _matrix_dims.cols; ++col)
    {
      norm += ((*this) (row, col)) * ((*this) (row, col));
    }
  }
  return norm;
}


/**
 *An overload to the [] operator , returns the (i) cell of the matrix if it
 * was a one dimension array
 * @param  given index
 * @return the ith element of the matrix
 */

float& Matrix::operator[] (int i)
{
  int matrix_len = _matrix_dims.cols * _matrix_dims.rows;
  if((i < 0) ||(matrix_len <= i)){
    throw std::out_of_range(OUT_OF_RANGE2);

  }
  return _data[i];
}



/**
 *A const overload to the [] operator , returns the (i) cell of the matrix if
 * it was a one dimension array
 * @param  given index
 * @return the ith element of the matrix
 */

float Matrix::operator[] (int i) const
{
  int matrix_len = _matrix_dims.cols * _matrix_dims.rows;
  if((i < 0) ||(matrix_len <= i)){
    throw std::out_of_range(OUT_OF_RANGE2);

  }
  return _data[i];
}

/**
 * An overload to the >> operator, reads binary file and inserts values into
 * matrix
 * @param input: input stream
 * @param matrix: the matrix that we will insert these values into
 * @return :same input stream
 */

std::istream& operator>>(std::istream &input, const Matrix &matrix){
  int dims = matrix.get_rows() * matrix.get_cols();
  if(!input.good()){
    throw std::runtime_error(FILE_ERROR);
  }
  input.read ((char*)matrix._data, sizeof(float)*dims);
  return input;

}

/**
 * An overload to the << operator, outputs the values of the matrix
 * @param os: output stream
 * @param matrix: the matrix who's values we will output
 * @return : same output stream
 */

std::ostream& operator<<(std::ostream &os, const Matrix &matrix){
  for ( int row = 0; row < matrix.get_rows(); ++row){
    for (int col = 0; col < matrix.get_cols(); ++col){
      if (matrix(row, col) > MIN_PROB){
        os << "**";
      }
      else{
        os << "  ";
      }

    }
    os << endl;
  }
  return os;
}

