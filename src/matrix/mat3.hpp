#pragma once

#include "matrix.hpp"

template <typename T>
using mat3 = Matrix<3, 3, T>;
using mat3f = mat3<Real>;

Real det(mat3f const &M);

mat3f inverse(mat3f const &M);
