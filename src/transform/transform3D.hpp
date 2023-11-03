#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat4.hpp"
#include "vector/vec3.hpp"
#include "units.hpp"

/// affine 3D transformation
struct Transform3D
{
  using MatrixType = Matrix<3, 4, float>;

  MatrixType transform_matrix;

  static Transform3D IDENTITY;

  static Transform3D rotation(vec3f const &axis, radf angle);
  static Transform3D scale(vec3f const &scale);
  static Transform3D scale(float scale);

  Transform3D inverse() const;
  mat4f as_mat4() const;
};