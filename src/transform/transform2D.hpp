#pragma once

#include "matrix/matrix_base.hpp"
#include "matrix/mat2.hpp"
#include "matrix/mat3.hpp"
#include "vector/vec2.hpp"
#include "units.hpp"
#include "geometry/point.hpp"
#include "vector/unit_vector.hpp"

/// Affine 2D transformation
struct Transform2D
{
  mat2f matrix = mat2f::diagonal(1._r);
  Vec2f translation = Vec2f{ 0._r, 0._r };

  static Transform2D const IDENTITY;

  static Transform2D rotate(Radf angle);
  static Transform2D scale(Vec2f const &scale);
  static Transform2D scale(Real scale);
  static Transform2D translate(Vec2f const &v);
  static Transform2D skew(Radf angle, UnitVec<Vec2f> const &direction,
      UnitVec<Vec2f> const &perpendicular);

  Transform2D inverse() const;
  mat3f as_mat3() const;
};

/// Combines transformations, with rhs being applied first and lhs
/// second.
Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs);

/// Transforms vector rhs by the transformation lhs.
/// This operation is equivalent to:
/// @code
/// auto const v = truncate(lhs.as_mat3() * Vec3f{ rhs.x, rhs.y, 0 });
/// @endcode
Vec2f operator*(Transform2D const &lhs, Vec2f const &rhs);

/// Transforms point rhs by the transformation lhs.
Point2f operator*(Transform2D const &lhs, Point2f const &rhs);
