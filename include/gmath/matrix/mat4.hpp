#pragma once

#include "gmath/matrix/matrix.hpp"

namespace gmath
{

template <typename T>
using mat4 = Matrix<4, 4, T>;
using mat4f = mat4<Real>;

Real det(mat4f const &M);
mat4f inverse(mat4f const &M);

}
