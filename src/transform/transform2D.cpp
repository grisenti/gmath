#include "transform2D.hpp"

#include <cmath>

#include "vec.hpp"

Transform2D const Transform2D::IDENTITY = Transform2D{
  .matrix = Mat2f::diagonal(1.f), .translation = Vec2f{0, 0}
};

Transform2D Transform2D::rotate(Radf angle)
{
  auto const angle_v = angle.value();
  // clang-format off
  return { Mat2f::from_rows({
      std::cos(angle_v), -std::sin(angle_v),
      std::sin(angle_v), std::cos(angle_v)
  }), Vec2f{0, 0}};
  // clang-format on
}

Transform2D Transform2D::scale(Vec2f const &scale)
{
  return {
    .matrix = Mat2f::diagonal(scale), .translation = Vec2f{0, 0}
  };
}

Transform2D Transform2D::scale(Real scale)
{
  return {
    .matrix = Mat2f::diagonal(scale), .translation = Vec2f{0, 0}
  };
}

Transform2D Transform2D::translate(const Vec2f &v)
{
  return { .matrix = Mat2f::diagonal(1.0), .translation = v };
}

Transform2D Transform2D::skew(Radf angle, const UnitVec<Vec2f> &direction,
    const UnitVec<Vec2f> &perpendicular)
{
  auto const a = direction.unwrap();
  auto const b = perpendicular.unwrap();
  auto const t = std::tan(angle.value());
  auto const x = b.x * t;
  auto const y = b.y * t;
  // clang-format off
  auto const skew_matrix = Mat2f::from_rows({
    a.x * x + 1, a.x * y,
    a.y * x, a.y * y + 1
  });
  // clang-format on
  return {
    .matrix = skew_matrix, .translation = Vec2f{0, 0}
  };
}

Transform2D Transform2D::inverse() const
{
  auto const a = matrix.column(0);
  auto const b = matrix.column(1);
  auto const c = translation;

  auto const inv_det = 1._r / det(matrix);
  auto const r0 = Vec2f{ b.y, -b.x } * inv_det;
  auto const r1 = Vec2f{ -a.y, a.x } * inv_det;

  auto const inv_translation
      = Vec2f{ b.x * c.y - b.y * c.x, c.x * a.y - a.x * c.y } * inv_det;

  return { .matrix = Mat2f::from_row_vecs({ r0, r1 }),
    .translation = inv_translation };
}

Mat3f Transform2D::as_mat3() const
{
  // clang-format off
  return Mat3f::from_rows({
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
  return lhs.matrix * rhs + lhs.translation;
}