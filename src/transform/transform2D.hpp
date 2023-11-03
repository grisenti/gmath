#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat3.hpp"
#include "vector/vec2.hpp"
#include "units.hpp"

/// affine 2D transformation
struct Transform2D
{
  using MatrixType = Matrix<2, 3, float>;

  MatrixType transform_matrix;

  static Transform2D IDENTITY;

  static Transform2D rotation(radf angle);
  static Transform2D scale(vec2f const &scale);
  static Transform2D scale(float scale);
  static Transform2D translation(vec2f const &v);

  vec2f get_translation() const;
  vec2f get_scale() const;
  radf get_rotation_angle() const;

  Transform2D inverse() const;
  mat3f as_mat3() const;
};

Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs);

vec2f operator*(Transform2D const &lhs, vec2f const &rhs);