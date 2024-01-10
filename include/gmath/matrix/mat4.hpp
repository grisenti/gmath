#pragma once

#include "gmath/matrix/matrix.hpp"

namespace gmath
{

template <typename T>
using Mat4 = Matrix<4, 4, T>;
using Mat4f = Mat4<Real>;

Real det(Mat4f const &M);
Mat4f inverse(Mat4f const &M);

}
