#pragma once

#include "gmath/matrix/mat2.hpp"
#include "gmath/matrix/mat3.hpp"
#include "gmath/vector/vec2.hpp"
#include "gmath/units.hpp"
#include "gmath/geometry/point.hpp"
#include "gmath/vector/unit_vector.hpp"

namespace gmath
{

/// Affine 2D transformation
struct Transform2D
{
  Mat2f matrix = Mat2f::diagonal(1._r);
  Vec2f translation = Vec2f{ 0._r, 0._r };

  static Transform2D const IDENTITY;

  static Transform2D rotate(Radf angle);
  static Transform2D scale(Vec2f const &scale);
  static Transform2D scale(Real scale);
  static Transform2D translate(Vec2f const &v);
  static Transform2D skew(Radf angle, UnitVec<Vec2f> const &direction,
      UnitVec<Vec2f> const &perpendicular);

  Transform2D inverse() const;
  Mat3f as_mat3() const;
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

} // namespace gmath
