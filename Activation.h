
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>


typedef Matrix (*ActivationFunc) (const Matrix &matrix);

namespace activation{
    Matrix relu(const Matrix &matrix);
    Matrix softmax(const Matrix &matrix);
}



#endif //ACTIVATION_H