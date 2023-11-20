#pragma once

#include "matrix_base.hpp"

template <typename T>
using mat2 = Matrix<2, 2, T>;
using mat2f = mat2<Real>;

Real det(mat2f const &M);
mat2f inverse(mat2f const &M);