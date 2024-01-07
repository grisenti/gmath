#pragma once

#include "matrix.hpp"

template <typename T>
using Mat3 = Matrix<3, 3, T>;
using Mat3f = Mat3<Real>;

Real det(Mat3f const &M);

Mat3f adj(Mat3f const &M);

Mat3f inverse(Mat3f const &M);
