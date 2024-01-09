#pragma once

#include "gmath/matrix/matrix.hpp"

namespace gmath
{

template <typename T>
using Mat2 = Matrix<2, 2, T>;
using Mat2f = Mat2<Real>;

Real det(Mat2f const &M);
Mat2f inverse(Mat2f const &M);

} // namespace gmath
