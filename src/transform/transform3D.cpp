#include "gmath/transform/transform3D.hpp"

namespace gmath
{

Transform3D const Transform3D::IDENTITY = Transform3D{
  .matrix = Mat3f::diagonal(1.f), .translation = Vec3f{0, 0, 0}
};

Transform3D Transform3D::rotate(Radf const angle, UnitVec<Vec3f> const &u_axis)
{
  auto const angle_v = angle.value();
  auto const axis = u_axis.unwrap();
  auto const c = std::cos(angle_v);
  auto const s = std::sin(angle_v);
  auto const t = 1 - c;
  // clang-format off
  auto const rotation_matrix = Mat3f::from_rows({
    c + t * pow2(axis.x), t * axis.x * axis.y - s * axis.z, t * axis.x * axis.z + s * axis.y,
    t * axis.x * axis.y + s * axis.z, c + t * pow2(axis.y), t * axis.y * axis.z - s * axis.x,
    t * axis.x * axis.z - s * axis.y, t * axis.y * axis.z + s * axis.x, c + t * pow2(axis.z)
  });
  // clang-format on

  return {
    .matrix = rotation_matrix, .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::scale(Vec3f const &scale)
{
  return {
    .matrix = Mat3f::diagonal(scale), .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::scale(Real scale)
{
  return {
    .matrix = Mat3f::diagonal(scale), .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::translate(Vec3f const &v)
{
  return { .matrix = Mat3f::diagonal(1.0), .translation = v };
}

Transform3D Transform3D::skew(Radf angle, const UnitVec<Vec3f> &direction,
    const UnitVec<Vec3f> &perpendicular)
{
  auto const a = direction.unwrap();
  auto const b = perpendicular.unwrap();
  auto const t = std::tan(angle.value());
  auto const x = b.x * t;
  auto const y = b.y * t;
  auto const z = b.z * t;
  // clang-format off
  auto const skew_matrix = Mat3f::from_rows({
    a.x * x + 1, a.x * y, a.x * z,
    a.y * x, a.y * y + 1, a.y * z,
    a.z * x, a.z * y, a.z * z + 1
  });
  // clang-format on
  return {
    .matrix = skew_matrix, .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::reflect(NormalizedPlane const &plane)
{
  auto const &n = plane.normal.unwrap();
  auto const d = plane.d;
  // clang-format off
  auto const reflection_matrix = Mat3f::from_rows({
      1 - 2 * pow2(n.x), -2 * n.x * n.y, -2 * n.x * n.z,
      -2 * n.y * n.x, 1 - 2 * pow2(n.y), -2 * n.y * n.z,
      -2 * n.z * n.x, -2 * n.z * n.y, 1 - 2 * pow2(n.z)
  });
  // clang-format on
  return { .matrix = reflection_matrix, .translation = as_vec3(-2 * d * n) };
}

Transform3D Transform3D::inverse() const
{
  auto const a = matrix.column(0);
  auto const b = matrix.column(1);
  auto const c = matrix.column(2);
  auto const d = translation;

  auto const s = cross(a, b);
  auto const t = cross(c, d);

  auto const inv_det = 1._r / dot(s, c);

  auto const inv_matrix = Mat3f::from_row_vecs(
      { cross(b, c) * inv_det, cross(c, a) * inv_det, s * inv_det });
  auto const inv_translation
      = Vec3f{ -dot(b, t), dot(a, t), -dot(d, s) } * inv_det;

  return { .matrix = inv_matrix, .translation = inv_translation };
}

Mat4f Transform3D::as_mat4() const
{
  // clang-format off
  return Mat4f::from_rows({
    matrix[0, 0], matrix[0, 1], matrix[0, 2], translation.x,
    matrix[0, 1], matrix[1, 1], matrix[1, 2], translation.y,
    matrix[0, 2], matrix[1, 2], matrix[2, 2], translation.z,
    0, 0, 0, 1
  });
  // clang-format on
}

Transform3D operator*(Transform3D const &lhs, Transform3D const &rhs)
{
  return { .matrix = lhs.matrix * rhs.matrix,
    .translation = lhs.translation + lhs.matrix * rhs.translation };
}

Vec3f operator*(Transform3D const &lhs, Vec3f const &rhs)
{
  return lhs.matrix * rhs;
}

Point3f operator*(Transform3D const &lhs, Point3f const &rhs)
{
  return lhs.matrix * rhs + lhs.translation;
}

Normal3f operator*(Normal3f const &lhs, Transform3D const &rhs)
{
  return lhs * rhs.matrix;
}

Plane operator*(Plane const &lhs, Transform3D const &rhs)
{
  return { lhs.normal * rhs.matrix, lhs.d + dot(lhs.normal, rhs.translation) };
}

} // namespace gmath