#include "test.hpp"

#include "gmath/mat.hpp"
#include "gmath/vec.hpp"
#include "gmath/geometry/normal3.hpp"

static void is_identity(Mat3f const &M)
{
  using Catch::Matchers::WithinAbs;
  REQUIRE_THAT((M[0, 0]), WithinAbs(1, 0.0001));
  REQUIRE_THAT((M[0, 1]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[0, 2]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[1, 0]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[1, 1]), WithinAbs(1, 0.0001));
  REQUIRE_THAT((M[1, 2]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 0]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 1]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 2]), WithinAbs(1, 0.0001));
}

static void is_identity(Mat4f const &M)
{
  using Catch::Matchers::WithinAbs;
  REQUIRE_THAT((M[0, 0]), WithinAbs(1, 0.0001));
  REQUIRE_THAT((M[0, 1]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[0, 2]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[0, 3]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[1, 0]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[1, 1]), WithinAbs(1, 0.0001));
  REQUIRE_THAT((M[1, 2]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[1, 3]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 0]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 1]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[2, 2]), WithinAbs(1, 0.0001));
  REQUIRE_THAT((M[2, 3]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[3, 0]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[3, 1]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[3, 2]), WithinAbs(0, 0.0001));
  REQUIRE_THAT((M[3, 3]), WithinAbs(1, 0.0001));
}

TEST_CASE("matrix_from_diagonal_value")
{
  auto const m = Mat3f::diagonal(1);
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 1] == 1);
  REQUIRE(m[2, 2] == 1);
}

TEST_CASE("non_square_matrix_from_diagonal_value")
{
  auto const m = Matrix<3, 4, int>::diagonal(1);
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 1] == 1);
  REQUIRE(m[2, 2] == 1);
  REQUIRE(m[0, 3] == 0);
  REQUIRE(m[1, 3] == 0);
  REQUIRE(m[2, 3] == 0);
}

TEST_CASE("square_matrix_from_diagonal_vector")
{
  auto const m = Mat3f::diagonal({ 1, 2, 3 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 1] == 2);
  REQUIRE(m[2, 2] == 3);
}

TEST_CASE("non_square_matrix_from_diagonal_vector")
{
  auto const m = Matrix<3, 4, int>::diagonal({ 1, 2, 3 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 1] == 2);
  REQUIRE(m[2, 2] == 3);
  REQUIRE(m[0, 3] == 0);
  REQUIRE(m[1, 3] == 0);
  REQUIRE(m[2, 3] == 0);
}

TEST_CASE("square_matrix_from_row_values")
{
  auto const m = Mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 2);
  REQUIRE(m[0, 2] == 3);
  REQUIRE(m[1, 0] == 4);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[1, 2] == 6);
  REQUIRE(m[2, 0] == 7);
  REQUIRE(m[2, 1] == 8);
  REQUIRE(m[2, 2] == 9);
}

TEST_CASE("square_matrix_from_row_vectors")
{
  auto const m = Mat3<int>::from_row_vecs({
      Vec3i{ 1, 2, 3 },
      Vec3i{ 4, 5, 6 },
      Vec3i{ 7, 8, 9 }
  });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 2);
  REQUIRE(m[0, 2] == 3);
  REQUIRE(m[1, 0] == 4);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[1, 2] == 6);
  REQUIRE(m[2, 0] == 7);
  REQUIRE(m[2, 1] == 8);
  REQUIRE(m[2, 2] == 9);
}

TEST_CASE("non_square_matrix_row_values")
{
  auto const m
      = Matrix<3, 4, int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 2);
  REQUIRE(m[0, 2] == 3);
  REQUIRE(m[0, 3] == 4);
  REQUIRE(m[1, 0] == 5);
  REQUIRE(m[1, 1] == 6);
  REQUIRE(m[1, 2] == 7);
  REQUIRE(m[1, 3] == 8);
  REQUIRE(m[2, 0] == 9);
  REQUIRE(m[2, 1] == 10);
  REQUIRE(m[2, 2] == 0);
  REQUIRE(m[2, 3] == 0);
}

TEST_CASE("non_square_matrix_from_row_vectors")
{
  auto const m = Matrix<3, 4, int>::from_row_vecs({
      Vec4i{ 1, 2,  3, 4 },
      Vec4i{ 5, 6,  7, 8 },
      Vec4i{ 9, 10, 0, 0 }
  });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 2);
  REQUIRE(m[0, 2] == 3);
  REQUIRE(m[0, 3] == 4);
  REQUIRE(m[1, 0] == 5);
  REQUIRE(m[1, 1] == 6);
  REQUIRE(m[1, 2] == 7);
  REQUIRE(m[1, 3] == 8);
  REQUIRE(m[2, 0] == 9);
  REQUIRE(m[2, 1] == 10);
  REQUIRE(m[2, 2] == 0);
  REQUIRE(m[2, 3] == 0);
}

TEST_CASE("square_matrix_from_column_values")
{
  auto const m = Mat3<int>::from_columns({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 4);
  REQUIRE(m[0, 2] == 7);
  REQUIRE(m[1, 0] == 2);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[1, 2] == 8);
  REQUIRE(m[2, 0] == 3);
  REQUIRE(m[2, 1] == 6);
  REQUIRE(m[2, 2] == 9);
}

TEST_CASE("square_matrix_from_column_vectors")
{
  auto const m = Mat3<int>::from_column_vecs({
      Vec3i{ 1, 2, 3 },
      Vec3i{ 4, 5, 6 },
      Vec3i{ 7, 8, 9 }
  });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[0, 1] == 4);
  REQUIRE(m[0, 2] == 7);
  REQUIRE(m[1, 0] == 2);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[1, 2] == 8);
  REQUIRE(m[2, 0] == 3);
  REQUIRE(m[2, 1] == 6);
  REQUIRE(m[2, 2] == 9);
}

TEST_CASE("non_square_matrix_from_column_values")
{
  auto const m = Matrix<3, 4, int>::from_columns(
      { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 0] == 2);
  REQUIRE(m[2, 0] == 3);
  REQUIRE(m[0, 1] == 4);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[2, 1] == 6);
  REQUIRE(m[0, 2] == 7);
  REQUIRE(m[1, 2] == 8);
  REQUIRE(m[2, 2] == 9);
  REQUIRE(m[0, 3] == 10);
  REQUIRE(m[1, 3] == 11);
  REQUIRE(m[2, 3] == 12);
}

TEST_CASE("non_square_matrix_from_column_vectors")
{
  auto const m = Matrix<3, 4, int>::from_column_vecs({
      Vec3i{ 1,  2,  3  },
      Vec3i{ 4,  5,  6  },
      Vec3i{ 7,  8,  9  },
      Vec3i{ 10, 11, 12 }
  });
  REQUIRE(m[0, 0] == 1);
  REQUIRE(m[1, 0] == 2);
  REQUIRE(m[2, 0] == 3);
  REQUIRE(m[0, 1] == 4);
  REQUIRE(m[1, 1] == 5);
  REQUIRE(m[2, 1] == 6);
  REQUIRE(m[0, 2] == 7);
  REQUIRE(m[1, 2] == 8);
  REQUIRE(m[2, 2] == 9);
  REQUIRE(m[0, 3] == 10);
  REQUIRE(m[1, 3] == 11);
  REQUIRE(m[2, 3] == 12);
}

TEST_CASE("matrix_get_row")
{
  auto const m = Mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(Vec3i{ m.row(0) } == Vec3i{ 1, 2, 3 });
  REQUIRE(Vec3i{ m.row(1) } == Vec3i{ 4, 5, 6 });
  REQUIRE(Vec3i{ m.row(2) } == Vec3i{ 7, 8, 9 });
}

TEST_CASE("matrix_get_column")
{
  auto const m = Mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(Vec3i{ m.column(0) } == Vec3i{ 1, 4, 7 });
  REQUIRE(Vec3i{ m.column(1) } == Vec3i{ 2, 5, 8 });
  REQUIRE(Vec3i{ m.column(2) } == Vec3i{ 3, 6, 9 });
}

TEST_CASE("square_matrix_multiplication")
{
  auto const m1 = Mat3<int>::from_rows({ 1, 3, 5, 9, 0, 20, 4, 2, 3 });
  auto const m2 = Mat3<int>::from_rows({ 4, 3, 9, 2, 0, 3, 2, 7, 50 });
  auto const result = m1 * m2;
  REQUIRE(Vec3i{ result.row(0) } == Vec3i{ 20, 38, 268 });
  REQUIRE(Vec3i{ result.row(1) } == Vec3i{ 76, 167, 1081 });
  REQUIRE(Vec3i{ result.row(2) } == Vec3i{ 26, 33, 192 });
}

TEST_CASE("non_square_matrix_multiplication")
{
  auto const m1
      = Matrix<3, 4, int>::from_rows({ 1, 3, 5, 9, 0, 20, 4, 2, 3, 1, 2, 3 });
  auto const m2 = Matrix<4, 2, int>::from_rows({ 4, 3, 9, 2, 0, 3, 2, 7 });
  auto const result = m1 * m2;
  REQUIRE(Vec2i{ result.row(0) } == Vec2i{ 49, 87 });
  REQUIRE(Vec2i{ result.row(1) } == Vec2i{ 184, 66 });
  REQUIRE(Vec2i{ result.row(2) } == Vec2i{ 27, 38 });
}

TEST_CASE("square_matrix_vector_multiplication")
{
  auto const m1 = Mat3f::diagonal({ 1, 2, 3 });
  auto const v1 = Vec3f{ 1, 2, 3 };
  auto const v2 = m1 * v1;
  REQUIRE(v2.x == 1);
  REQUIRE(v2.y == 4);
  REQUIRE(v2.z == 9);
}

TEST_CASE("non_square_matrix_vector_multiplication")
{
  auto const m1 = Matrix<4, 3, int>::diagonal({ 1, 2, 3 });
  auto const v1 = Vec4i{ 1, 2, 3, 4 };
  auto const v2 = m1 * v1;
  REQUIRE(v2.x == 1);
  REQUIRE(v2.y == 4);
  REQUIRE(v2.z == 9);
  REQUIRE(v2.w == 0);
}

TEST_CASE("row_matrix_mul_square_matrix")
{
  auto const m1 = Mat3<int>::from_columns({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  auto const n1 = Normal3<int>{ 1, 1, 1 };
  auto const v2 = n1 * m1;
  REQUIRE(v2.x == 6);
  REQUIRE(v2.y == 15);
  REQUIRE(v2.z == 24);
}

TEST_CASE("inline_transpose")
{
  auto m1 = Mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  m1.transpose();
  REQUIRE(Vec3i{ m1.row(0) } == Vec3i{ 1, 4, 7 });
  REQUIRE(Vec3i{ m1.row(1) } == Vec3i{ 2, 5, 8 });
  REQUIRE(Vec3i{ m1.row(2) } == Vec3i{ 3, 6, 9 });
}

TEST_CASE("transpose_matrix")
{
  auto const m1 = Mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  auto const m2 = transpose(m1);
  REQUIRE(Vec3i{ m2.row(0) } == Vec3i{ 1, 4, 7 });
  REQUIRE(Vec3i{ m2.row(1) } == Vec3i{ 2, 5, 8 });
  REQUIRE(Vec3i{ m2.row(2) } == Vec3i{ 3, 6, 9 });
}

TEST_CASE("transpose_non_square")
{
  auto const m1 = Matrix<3, 4, int>::from_rows(
      { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
  auto const m2 = transpose(m1);
  REQUIRE(Vec4i{ m2.column(0) } == Vec4i{ 1, 2, 3, 4 });
  REQUIRE(Vec4i{ m2.column(1) } == Vec4i{ 5, 6, 7, 8 });
  REQUIRE(Vec4i{ m2.column(2) } == Vec4i{ 9, 10, 11, 12 });
}

TEST_CASE("matrix_3x3_determinant")
{
  auto const m1 = Mat3f::from_rows({ 1, 2, 3, 3, 2, 1, 2, 1, 3 });
  auto const result = det(m1);
  REQUIRE(result == Catch::Approx(-12));
}

TEST_CASE("matrix_3x3_adjugate")
{
  auto const m1 = Mat3f::from_rows({ 1, 2, 3, 3, 2, 1, 2, 1, 3 });
  auto const m2 = adj(m1);
  REQUIRE(m2.row(0) == Vec3f{ 5, -3, -4 });
  REQUIRE(m2.row(1) == Vec3f{ -7, -3, 8 });
  REQUIRE(m2.row(2) == Vec3f{ -1, 3, -4 });
}

TEST_CASE("matrix_3x3_inverse")
{
  auto const m1 = Mat3f::from_rows({ 4, 7, 14, 5, 20, 4, 0, 10, 6 });
  auto const m2 = inverse(m1);
  is_identity(m1 * m2);
  is_identity(m2 * m1);
}

TEST_CASE("matrix_4x4_determinant")
{
  auto const m1 = Mat4f::from_rows(
      { 1, 2, 3, 4, -2, 1, -4, 3, 3, -4, -1, 2, 4, 3, -2, -1 });
  auto const result = det(m1);
  REQUIRE(result == Catch::Approx(900));
}

TEST_CASE("matrix_4x4_inverse")
{
  auto const m1
      = Mat4f::from_rows({ 3, 3, 3, 1, 2, 4, 5, 2, 3, 4, 5, 1, 2, 2, 3, 4 });
  auto const m2 = inverse(m1);
  is_identity(m1 * m2);
  is_identity(m2 * m1);
}
