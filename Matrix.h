// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;


class Matrix{
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &matrix);
  ~Matrix();
  int get_rows() const;
  int get_cols() const;
  Matrix& transpose();
  Matrix vectorize();
  void plain_print() const;
  Matrix dot(const Matrix &other);
  float norm() const ;
  int argmax() const;
  Matrix operator+(const Matrix &other) const;
  Matrix& operator=(const Matrix &other);
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const float &right_scalar) const;
  friend Matrix operator*(const float &left_scalar, const Matrix &other);
  Matrix& operator+=(const Matrix &other);
  float& operator()(const int &i, const int &j);
  float operator()(const int &i, const int &j) const; //// מעתיק
  float& operator[](int i);
  float operator[](int i) const;
  friend std::istream &operator>>(std::istream &input, const Matrix &matrix);
  friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix);
 private:
  matrix_dims _matrix_dims;
  float* _data;


};


#endif //MATRIX_H