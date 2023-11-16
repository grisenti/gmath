#include "test.hpp"

#include "geometry/point.hpp"

TEST_CASE("Point2_direction")
{
  Point2i p1{ 1, 1 };
  Point2i p2{ 2, 2 };
  auto const result = p2 - p1;
  Vec2i expected{ 1, 1 };
  REQUIRE(result == expected);
}

TEST_CASE("add_vector_to_Point2")
{
  Point2i p1{ 1, 1 };
  Vec2i v1{ 2, 2 };
  auto const result = p1 + v1;
  Point2i expected{ 3, 3 };
  REQUIRE(result == expected);
}

TEST_CASE("Point3_direction")
{
  Point3i p1{ 1, 1, 1 };
  Point3i p2{ 2, 2, 2 };
  auto const result = p2 - p1;
  Vec3i expected{ 1, 1, 1 };
  REQUIRE(result == expected);
}

TEST_CASE("add_vector_to_Point3")
{
  Point3i p1{ 1, 1, 1 };
  Vec3i v1{ 2, 2, 2 };
  auto const result = p1 + v1;
  Point3i expected{ 3, 3, 3 };
  REQUIRE(result == expected);
}