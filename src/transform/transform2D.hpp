#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat2.hpp"
#include "matrix/mat3.hpp"
#include "vector/vec2.hpp"
#include "units.hpp"

/// affine 2D transformation
struct Transform2D
{
  mat2f matrix = mat2f::diagonal(1.f);
  vec2f translation = vec2f{ 0, 0 };

  static Transform2D IDENTITY;

  static Transform2D from_rotation(radf angle);
  static Transform2D from_scale(vec2f const &scale);
  static Transform2D from_scale(float scale);
  static Transform2D from_translation(vec2f const &v);

  Transform2D inverse() const;
  mat3f as_mat3() const;
};

Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs);

vec2f operator*(Transform2D const &lhs, vec2f const &rhs);