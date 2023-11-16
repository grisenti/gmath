#include "transform2D.hpp"

#include <cmath>

#include "vec.hpp"

Transform2D Transform2D::IDENTITY = Transform2D{
  .matrix = mat2f::diagonal(0.f), .translation = Vec2f{0, 0}
};

Transform2D Transform2D::from_rotation(Radf const angle)
{
  auto const angle_v = angle.value();
  // clang-format off
  return { mat2f::from_rows({
      std::cos(angle_v), -std::sin(angle_v),
      std::sin(angle_v), std::cos(angle_v)
  }), Vec2f{0, 0}};
  // clang-format on
}

Transform2D Transform2D::from_scale(Vec2f const &scale)
{
  return {
    .matrix = mat2f::diagonal(scale), .translation = Vec2f{0, 0}
  };
}

Transform2D Transform2D::from_scale(float scale)
{
  return {
    .matrix = mat2f::diagonal(scale), .translation = Vec2f{0, 0}
  };
}

Transform2D Transform2D::from_translation(const Vec2f &v)
{
  return { .matrix = mat2f::diagonal(1.0), .translation = v };
}

Transform2D Transform2D::inverse() const
{
  return { .matrix = ::inverse(matrix), .translation = -translation };
}

mat3f Transform2D::as_mat3() const
{
  // clang-format off
  return mat3f::from_rows({
      matrix[0, 0], matrix[0, 1], translation.x,
      matrix[0, 1], matrix[1, 1], translation.y,
      0, 0, 1
  });
  // clang-format on
}

Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs)
{
  return { .matrix = lhs.matrix * rhs.matrix,
    .translation = lhs.matrix * rhs.translation + lhs.translation };
}

Vec2f operator*(Transform2D const &lhs, Vec2f const &rhs)
{
  return lhs.matrix * rhs;
}

Point2f operator*(Transform2D const &lhs, Point2f const &rhs)
{
  auto const x = lhs.matrix[0, 0] * rhs.x + lhs.matrix[0, 1] * rhs.y
                 + lhs.translation.x;
  auto const y = lhs.matrix[1, 0] * rhs.x + lhs.matrix[1, 1] * rhs.y
                 + lhs.translation.y;
  return { x, y };
}