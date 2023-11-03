#pragma once

#include "matrix_base.hpp"

template <typename T>
using mat4 = Matrix<4, 4, T>;
using mat4f = mat4<float>;

float det(mat4f const &M);

mat4f inverse(mat4f const &M);