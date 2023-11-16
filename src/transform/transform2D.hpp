#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat2.hpp"
#include "matrix/mat3.hpp"
#include "vector/vec2.hpp"
#include "units.hpp"

/// Affine 2D transformation
struct Transform2D
{
  mat2f matrix = mat2f::diagonal(1.f);
  Vec2f translation = Vec2f{ 0, 0 };

  static Transform2D IDENTITY;

  static Transform2D from_rotation(Radf angle);
  static Transform2D from_scale(Vec2f const &scale);
  static Transform2D from_scale(float scale);
  static Transform2D from_translation(Vec2f const &v);

  Transform2D inverse() const;
  mat3f as_mat3() const;
};

/// Combines transformations, with rhs being applied first and lhs
/// second.
Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs);

/// Transforms vector rhs by the transformation lhs.
/// This operation is equivalent to:
/// @code
/// auto const v = truncate(lhs.as_mat3() * Vec3f{ rhs.x, rhs.y, 1 });
/// @endcode
Vec2f operator*(Transform2D const &lhs, Vec2f const &rhs);
