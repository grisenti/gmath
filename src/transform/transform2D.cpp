#include "transform2D.hpp"

#include <cmath>

#include "vec.hpp"

Transform2D Transform2D::IDENTITY
    = Transform2D{ Matrix<2, 3, float>::diagonal(1.0f) };

Transform2D Transform2D::rotation(radf const angle)
{
  auto const angle_v = angle.value;
  // clang-format off
  return { MatrixType::from_rows({
      std::cos(angle_v), -std::sin(angle_v), 0,
      std::sin(angle_v), std::cos(angle_v), 0
  })};
  // clang-format on
}

Transform2D Transform2D::scale(vec2f const &scale)
{
  return { MatrixType::diagonal(scale) };
}

Transform2D Transform2D::scale(float scale)
{
  return { MatrixType::diagonal(scale) };
}

Transform2D Transform2D::translation(const vec2f &v)
{
  return { MatrixType::from_rows({ 1, 0, v.x, 0, 1, v.y }) };
}

vec2f Transform2D::get_translation() const
{
  return transform_matrix.column(2);
}

vec2f Transform2D::get_scale() const
{
  return vec2f();
}

radf Transform2D::get_rotation_angle() const
{
  return radf(0);
}

Transform2D Transform2D::inverse() const
{
  return Transform2D();
}

mat3f Transform2D::as_mat3() const
{
  // clang-format off
  return mat3f::from_rows({
      transform_matrix[0, 0], transform_matrix[0, 1], transform_matrix[0, 2],
      transform_matrix[0, 1], transform_matrix[1, 1], transform_matrix[1, 2],
      0, 0, 1
  });
  // clang-format on
}

Transform2D operator*(Transform2D const &lhs, Transform2D const &rhs)
{
  return { lhs.transform_matrix * rhs.as_mat3() };
}

vec2f operator*(Transform2D const &lhs, vec2f const &rhs)
{
  return truncate(lhs.transform_matrix * extend(rhs, 1.f));
}