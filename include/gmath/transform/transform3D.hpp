#pragma once

#include "gmath/matrix/mat3.hpp"
#include "gmath/matrix/mat4.hpp"
#include "gmath/vector/vec3.hpp"
#include "gmath/geometry/normal3.hpp"
#include "gmath/vector/unit_vector.hpp"
#include "gmath/units.hpp"
#include "gmath/geometry/point.hpp"
#include "gmath/geometry/plane.hpp"

namespace gmath
{

/// affine 3D transformation
struct Transform3D
{
  Mat3f matrix;
  Vec3f translation;

  static Transform3D const IDENTITY;

  static Transform3D rotate(Radf angle, UnitVec<Vec3f> const &axis);
  static Transform3D scale(Vec3f const &scale);
  static Transform3D scale(Real scale);
  static Transform3D translate(Vec3f const &v);
  static Transform3D skew(Radf angle, UnitVec<Vec3f> const &direction,
      UnitVec<Vec3f> const &perpendicular);
  static Transform3D reflect(NormalizedPlane const &plane);
  static Transform3D orthographic(float left, float right, float bottom,
      float top, float near,
      float far);

  Transform3D inverse() const;
  Mat4f as_mat4() const;
};

/// combines transformations, with `rhs` being applied first and `lhs` second
Transform3D operator*(Transform3D const &lhs, Transform3D const &rhs);

/// transforms vector `rhs` by the transformation `lhs`
Vec3f operator*(Transform3D const &lhs, Vec3f const &rhs);

/// Transforms point @param rhs by the transformation @param lhs.
Point3f operator*(Transform3D const &lhs, Point3f const &rhs);

/// Transforms the normal @param rhs by the transformation @param lhs.
Normal3f operator*(Normal3f const &lhs, Transform3D const &rhs);

/// Transforms the plane @param rhs by the transformation @param lhs.
Plane operator*(Plane const &lhs, Transform3D const &rhs);

} // namespace gmath