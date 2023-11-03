#include "test.hpp"

#include "vec.hpp"

TEST_CASE("vector_addition")
{
  vec3i v1{ 1, 2, 3 };
  vec3i v2{ 4, 5, 6 };
  vec3i result = v1 + v2;
  vec3i expected{ 5, 7, 9 };
  REQUIRE(result == expected);
}

TEST_CASE("vector_subtraction")
{
  vec3i v1{ 1, 2, 3 };
  vec3i v2{ 4, 5, 6 };
  vec3i result = v1 - v2;
  vec3i expected{ -3, -3, -3 };
  REQUIRE(result == expected);
}

TEST_CASE("vector_unary_minus")
{
  vec3i v1{ 1, 2, 3 };
  vec3i result = -v1;
  vec3i expected{ -1, -2, -3 };
  REQUIRE(result == expected);
}

TEST_CASE("vector_scalar_multiplication")
{
  vec3i v1{ 1, 2, 3 };
  int scalar = 2;
  vec3i expected{ 2, 4, 6 };
  vec3i result = v1 * scalar;
  REQUIRE(result == expected);
  result = scalar * v1;
  REQUIRE(result == expected);
}

TEST_CASE("vector_dot_product")
{
  vec3i v1{ 1, 2, 3 };
  vec3i v2{ 4, 5, 6 };
  auto const expected = 32;
  auto result = dot(v1, v2);
  REQUIRE(result == expected);
  result = dot(v2, v1);
  REQUIRE(result == expected);
}

TEST_CASE("vector_cross_product")
{
  vec3i v1{ 1, 2, 3 };
  vec3i v2{ 4, 5, 6 };
  vec3i expected{ -3, 6, -3 };
  auto result = cross(v1, v2);
  REQUIRE(result == expected);
  result = cross(v2, v1);
  REQUIRE(result == -expected);
}

TEST_CASE("vector_length")
{
  vec3f v1{ 4, 9, 5 };
  auto const result = length(v1);
  auto const expected = Catch::Approx(11.045361017);
  REQUIRE(result == expected);
}

TEST_CASE("vector_distance")
{
  vec3f v1{ 5, 0, 100 };
  vec3f v2{ 4.2f, 5.3f, 6.9f };
  auto const result = distance(v1, v2);
  auto const expected = Catch::Approx(93.254168808);
  REQUIRE(result == expected);
}

TEST_CASE("vector_normalize")
{
  vec3f v1{ 2.59f, 50.90f, 0 };
  vec3f result = normalize(v1);
  REQUIRE(result.x == Catch::Approx(0.05081834));
  REQUIRE(result.y == Catch::Approx(0.998707913));
  REQUIRE(result.z == Catch::Approx(0));
}

TEST_CASE("vector_project")
{
  vec3f v1{ 1, 2, 3 };
  vec3f v2{ 4, 5, 6 };
  vec3f result = project(v1, v2);
  REQUIRE(result.x == Catch::Approx(1.662337662));
  REQUIRE(result.y == Catch::Approx(2.077922078));
  REQUIRE(result.z == Catch::Approx(2.493506494));
}

TEST_CASE("vector_reject")
{
  vec3f v1{ 1, 2, 3 };
  vec3f v2{ 4, 5, 6 };
  vec3f result = reject(v1, v2);
  REQUIRE(result.x == Catch::Approx(-0.662337));
  REQUIRE(result.y == Catch::Approx(-0.077922));
  REQUIRE(result.z == Catch::Approx(0.506493));
}

TEST_CASE("vector_extend")
{
  vec3i v1{ 1, 2, 3 };
  vec4i expected{ 1, 2, 3, 7 };
  REQUIRE(extend(v1, 7) == expected);
}