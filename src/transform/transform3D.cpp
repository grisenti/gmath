#include "transform3D.hpp"

Transform3D Transform3D::from_rotation(
    Radf const angle_rad, UnitVec<Vec3f> const &u_axis)
{
  auto const angle = angle_rad.value();
  auto const axis = u_axis.unwrap();
  auto const c = std::cos(angle);
  auto const s = std::sin(angle);
  auto const t = 1 - c;
  // clang-format off
  auto const rotation_matrix = mat3f::from_rows({
    c + t * pow2(axis.x), t * axis.x * axis.y - s * axis.z, t * axis.x * axis.z + s * axis.y,
    t * axis.x * axis.y + s * axis.z, c + t * pow2(axis.y), t * axis.y * axis.z - s * axis.x,
    t * axis.x * axis.z - s * axis.y, t * axis.y * axis.z + s * axis.x, c + t * pow2(axis.z)
  });
  // clang-format on

  return {
    .matrix = rotation_matrix, .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::from_scale(Vec3f const &scale)
{
  return {
    .matrix = mat3f::diagonal(scale), .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::from_scale(float const scale)
{
  return {
    .matrix = mat3f::diagonal(scale), .translation = Vec3f{0, 0, 0}
  };
}

Transform3D Transform3D::from_translation(Vec3f const &v)
{
  return { .matrix = mat3f::diagonal(1.0), .translation = v };
}

Transform3D Transform3D::inverse() const
{
  return { .matrix = ::inverse(matrix), .translation = -translation };
}

mat4f Transform3D::as_mat4() const
{
  // clang-format off
  return mat4f::from_rows({
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
  auto const x = lhs.matrix[0, 0] * rhs.x + lhs.matrix[0, 1] * rhs.y
                 + lhs.matrix[0, 2] * rhs.z + lhs.translation.x;
  auto const y = lhs.matrix[1, 0] * rhs.x + lhs.matrix[1, 1] * rhs.y
                 + lhs.matrix[1, 2] * rhs.z + lhs.translation.y;
  auto const z = lhs.matrix[2, 0] * rhs.x + lhs.matrix[2, 1] * rhs.y
                 + lhs.matrix[2, 2] * rhs.z + lhs.translation.z;
  return { x, y, z };
}