#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat3.hpp"
#include "matrix/mat4.hpp"
#include "vector/vec3.hpp"
#include "vector/unit_vector.hpp"
#include "units.hpp"

/// affine 3D transformation
struct Transform3D
{
  mat3f matrix;
  vec3f translation;

  static Transform3D IDENTITY;

  static Transform3D from_rotation(radf angle, UnitVec<vec3f> const &axis);
  static Transform3D from_scale(vec3f const &scale);
  static Transform3D from_scale(float scale);
  static Transform3D from_translation(vec3f const &v);

  Transform3D inverse() const;
  mat4f as_mat4() const;
};

/// combines transformations, with `rhs` being applied first and `lhs` second
Transform3D operator*(Transform3D const &lhs, Transform3D const &rhs);

/// transforms vector `rhs` by the transformation `lhs`
vec3f operator*(Transform3D const &lhs, vec3f const &rhs);