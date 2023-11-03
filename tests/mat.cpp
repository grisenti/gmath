#include "test.hpp"

#include "mat.hpp"
#include "vec.hpp"

static void is_identity(mat3f const &M)
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

static void is_identity(mat4f const &M)
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
  auto const m = mat3f::diagonal(1);
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
  auto const m = mat3f::diagonal({ 1, 2, 3 });
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
  auto const m = mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
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
  auto const m = mat3<int>::from_row_vecs({
      vec3i{1,  2, 3},
      vec3i{ 4, 5, 6},
      vec3i{ 7, 8, 9}
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
      vec4i{1,  2,  3, 4},
      vec4i{ 5, 6,  7, 8},
      vec4i{ 9, 10, 0, 0}
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
  auto const m = mat3<int>::from_columns({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
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
  auto const m = mat3<int>::from_column_vecs({
      vec3i{1,  2, 3},
      vec3i{ 4, 5, 6},
      vec3i{ 7, 8, 9}
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
      vec3i{1,   2,  3 },
      vec3i{ 4,  5,  6 },
      vec3i{ 7,  8,  9 },
      vec3i{ 10, 11, 12}
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
  auto const m = mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(vec3i{ m.row(0) } == vec3i{ 1, 2, 3 });
  REQUIRE(vec3i{ m.row(1) } == vec3i{ 4, 5, 6 });
  REQUIRE(vec3i{ m.row(2) } == vec3i{ 7, 8, 9 });
}

TEST_CASE("matrix_get_column")
{
  auto const m = mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  REQUIRE(vec3i{ m.column(0) } == vec3i{ 1, 4, 7 });
  REQUIRE(vec3i{ m.column(1) } == vec3i{ 2, 5, 8 });
  REQUIRE(vec3i{ m.column(2) } == vec3i{ 3, 6, 9 });
}

TEST_CASE("square_matrix_multiplication")
{
  auto const m1 = mat3<int>::from_rows({ 1, 3, 5, 9, 0, 20, 4, 2, 3 });
  auto const m2 = mat3<int>::from_rows({ 4, 3, 9, 2, 0, 3, 2, 7, 50 });
  auto const result = m1 * m2;
  REQUIRE(vec3i{ result.row(0) } == vec3i{ 20, 38, 268 });
  REQUIRE(vec3i{ result.row(1) } == vec3i{ 76, 167, 1081 });
  REQUIRE(vec3i{ result.row(2) } == vec3i{ 26, 33, 192 });
}

TEST_CASE("non_square_matrix_multiplication")
{
  auto const m1
      = Matrix<3, 4, int>::from_rows({ 1, 3, 5, 9, 0, 20, 4, 2, 3, 1, 2, 3 });
  auto const m2 = Matrix<4, 2, int>::from_rows({ 4, 3, 9, 2, 0, 3, 2, 7 });
  auto const result = m1 * m2;
  REQUIRE(vec2i{ result.row(0) } == vec2i{ 49, 87 });
  REQUIRE(vec2i{ result.row(1) } == vec2i{ 184, 66 });
  REQUIRE(vec2i{ result.row(2) } == vec2i{ 27, 38 });
}

TEST_CASE("square_matrix_vector_multiplication")
{
  auto const m1 = mat3f::diagonal({ 1, 2, 3 });
  auto const v1 = vec3f{ 1, 2, 3 };
  auto const v2 = m1 * v1;
  REQUIRE(v2.x == 1);
  REQUIRE(v2.y == 4);
  REQUIRE(v2.z == 9);
}

TEST_CASE("non_square_matrix_vector_multiplication")
{
  auto const m1 = Matrix<3, 4, int>::diagonal({ 1, 2, 3 });
  auto const v1 = vec4i{ 1, 2, 3, 4 };
  auto const v2 = m1 * v1;
  REQUIRE(v2.x == 1);
  REQUIRE(v2.y == 4);
  REQUIRE(v2.z == 9);
  REQUIRE(v2.w == 0);
}

TEST_CASE("inline_transpose")
{
  auto m1 = mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  m1.transpose();
  REQUIRE(vec3i{ m1.row(0) } == vec3i{ 1, 4, 7 });
  REQUIRE(vec3i{ m1.row(1) } == vec3i{ 2, 5, 8 });
  REQUIRE(vec3i{ m1.row(2) } == vec3i{ 3, 6, 9 });
}

TEST_CASE("transpose_matrix")
{
  auto const m1 = mat3<int>::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  auto const m2 = transpose(m1);
  REQUIRE(vec3i{ m2.row(0) } == vec3i{ 1, 4, 7 });
  REQUIRE(vec3i{ m2.row(1) } == vec3i{ 2, 5, 8 });
  REQUIRE(vec3i{ m2.row(2) } == vec3i{ 3, 6, 9 });
}

TEST_CASE("transpose_non_square")
{
  auto const m1 = Matrix<3, 4, int>::from_rows(
      { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
  auto const m2 = transpose(m1);
  REQUIRE(vec4i{ m2.column(0) } == vec4i{ 1, 2, 3, 4 });
  REQUIRE(vec4i{ m2.column(1) } == vec4i{ 5, 6, 7, 8 });
  REQUIRE(vec4i{ m2.column(2) } == vec4i{ 9, 10, 11, 12 });
}

TEST_CASE("matrix_3x3_determinant")
{
  auto const m1 = mat3f::from_rows({ 1, 2, 3, 3, 2, 1, 2, 1, 3 });
  auto const result = det(m1);
  REQUIRE(result == Catch::Approx(-12));
}

TEST_CASE("matrix_3x3_inverse")
{
  auto const m1 = mat3f::from_rows({ 4, 7, 14, 5, 20, 4, 0, 10, 6 });
  auto const m2 = inverse(m1);
  is_identity(m1 * m2);
  is_identity(m2 * m1);
}

TEST_CASE("matrix_4x4_determinant")
{
  auto const m1 = mat4f::from_rows(
      { 1, 2, 3, 4, -2, 1, -4, 3, 3, -4, -1, 2, 4, 3, -2, -1 });
  auto const result = det(m1);
  REQUIRE(result == Catch::Approx(900));
}

TEST_CASE("matrix_4x4_inverse")
{
  auto const m1
      = mat4f::from_rows({ 3, 3, 3, 1, 2, 4, 5, 2, 3, 4, 5, 1, 2, 2, 3, 4 });
  auto const m2 = inverse(m1);
  is_identity(m1 * m2);
  is_identity(m2 * m1);
}