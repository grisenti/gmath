#pragma once

#include "matrix_base.hpp"

template <typename T>
using mat3 = Matrix<3, 3, T>;
using mat3f = mat3<float>;

float det(mat3f const &M);

mat3f inverse(mat3f const &M);
