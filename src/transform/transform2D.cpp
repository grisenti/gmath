#include "transform2D.hpp"

#include <cmath>

#include "vec.hpp"

Transform2D Transform2D::IDENTITY = Transform2D{
  .matrix = mat2f::diagonal(0.f), .translation = vec2f{0, 0}
};

Transform2D Transform2D::from_rotation(radf const angle)
{
  auto const angle_v = angle.value;
  // clang-format off
  return { mat2f::from_rows({
      std::cos(angle_v), -std::sin(angle_v),
      std::sin(angle_v), std::cos(angle_v)
  })};
  // clang-format on
}

Transform2D Transform2D::from_scale(vec2f const &scale)
{
  return {
    .matrix = mat2f::diagonal(scale), .translation = vec2f{0, 0}
  };
}

Transform2D Transform2D::from_scale(float scale)
{
  return {
    .matrix = mat2f::diagonal(scale), .translation = vec2f{0, 0}
  };
}

Transform2D Transform2D::from_translation(const vec2f &v)
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
    .translation = rhs.translation + lhs.translation };
}

vec2f operator*(Transform2D const &lhs, vec2f const &rhs)
{
  return lhs.matrix * rhs + lhs.translation;
}