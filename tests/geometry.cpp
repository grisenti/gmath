#include "test.hpp"

#include "geometry/point.hpp"
#include "geometry/plane.hpp"
#include "geometry/line.hpp"

TEST_CASE("direction_from_pair_of_points")
{
  Point3i p1{ 1, 1, 1 };
  Point3i p2{ 2, 2, 2 };
  auto const result = p2 - p1;
  Vec3i expected{ 1, 1, 1 };
  REQUIRE(result == expected);
}

TEST_CASE("add_vector_to_point")
{
  Point2i p1{ 1, 1 };
  Vec2i v1{ 2, 2 };
  auto const result = p1 + v1;
  Point2i expected{ 3, 3 };
  REQUIRE(result == expected);
}

TEST_CASE("subtract_vector_from_point")
{
  Point2i p1{ 1, 1 };
  Vec2i v1{ 2, 2 };
  auto const result = p1 - v1;
  Point2i expected{ -1, -1 };
  REQUIRE(result == expected);
}

TEST_CASE("point_distance")
{
  Point2f p1{ 1, 1 };
  Point2f p2{ 2, 2 };
  auto const result = distance(p1, p2);
  REQUIRE(result == Catch::Approx(std::sqrt(2)));
}

TEST_CASE("correct_creation_of_normalized_plane_from_plane")
{
  auto const normal = Normal3f{ 1, 1, 1 };
  Plane plane{ normal, 1 };
  auto const normalized_plane = NormalizedPlane::from_plane(plane);
  REQUIRE(length(normalized_plane.normal) == Catch::Approx(1.0));
  REQUIRE(normalized_plane.d == Catch::Approx(1.0 / length(normal)));
}

TEST_CASE("distance_point_plane")
{
  auto const normal = Normal3f{ 1, 1, 1 };
  Plane plane{ normal, 0 };
  auto const normalized_plane = NormalizedPlane::from_plane(plane);
  auto const l = length(Vec3f{ 1, 1, 1 });
  REQUIRE(signed_distance(normalized_plane, { 1, 1, 1 }) == Catch::Approx(l));
  REQUIRE(
      signed_distance(normalized_plane, { -1, -1, -1 }) == Catch::Approx(-l));
}

TEST_CASE("intersect_planes")
{
  auto const p1 = Plane{
    {1, 0, 0},
    -3
  };
  auto const p2 = Plane{
    {0, 1, 0},
    -3
  };
  auto const p3 = Plane{
    {0, 0, 1},
    -3
  };
  auto const result = intersection_point(p1, p2, p3);
  REQUIRE(result.has_value());
  REQUIRE(result->x == Catch::Approx(3));
  REQUIRE(result->y == Catch::Approx(3));
  REQUIRE(result->z == Catch::Approx(3));
}

TEST_CASE("non_intersecting_planes_do_not_intersect")
{
  auto const p1 = Plane{
    {1, 0, 0},
    0
  };
  auto const p2 = Plane{
    {1, 0, 0},
    1
  };
  auto const p3 = Plane{
    {1, 0, 0},
    2
  };
  auto const result = intersection_point(p1, p2, p3);
  REQUIRE(!result.has_value());
}

TEST_CASE("normalized_line_from_line")
{
  auto const dir = Vec3f{ 1, 1, 1 };
  auto const l = length(dir);
  auto const moment = Normal3f{ 1, 1, 1 };
  auto const line = Line{ dir, moment };
  auto const normalized_line = NormalizedLine::from_line(line);
  REQUIRE(length(normalized_line.direction) == Catch::Approx(1.0));
  REQUIRE(length(normalized_line.moment) == Catch::Approx(length(moment) / l));
}