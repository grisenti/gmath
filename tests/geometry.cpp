#include "test.hpp"

#include "gmath/geometry.hpp"

TEST_CASE("point_iteration")
{
  Point3i p{ 1, 2, 3 };
  for (size_t i = 0; auto const &x : p)
  {
    REQUIRE(x == p[i]);
    i += 1;
  }
}

TEST_CASE("normal_iteration")
{
  Normal3f n{ 1, 2, 3 };
  for (size_t i = 0; auto const &x : n)
  {
    REQUIRE(x == n[i]);
    i += 1;
  }
}

TEST_CASE("point_three_way_comparison")
{
  Point3i p1{ 1, 2, 3 };
  Point3i p2{ 1, 2, 3 };
  REQUIRE(p1 <=> p2 == std::strong_ordering::equivalent);
  Point3i p3{ 1, 2, 4 };
  REQUIRE(p1 <=> p3 == std::strong_ordering::less);
  REQUIRE(p3 <=> p1 == std::strong_ordering::greater);
}

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

TEST_CASE("plane_from_three_points")
{
  Point3f p1{ 1, 0, 0 };
  Point3f p2{ 0, 1, 0 };
  Point3f p3{ 0, 0, 1 };
  auto const result = Plane::from_points(p1, p2, p3);
  Plane const expected{
    { 1, 1, 1 },
    -1
  };
  REQUIRE(result == expected);
}

TEST_CASE("correct_creation_of_normalized_plane_from_plane")
{
  auto const normal = Normal3f{ 1, 1, 1 };
  Plane plane{ normal, 1 };
  auto const normalized_plane = NormalizedPlane::from_plane(plane);
  REQUIRE(magnitude(normalized_plane.normal) == Catch::Approx(1.0));
  REQUIRE(normalized_plane.d == Catch::Approx(1.0 / magnitude(normal)));
}

TEST_CASE("distance_point_plane")
{
  auto const normal = Normal3f{ 1, 1, 1 };
  Plane plane{ normal, 0 };
  auto const normalized_plane = NormalizedPlane::from_plane(plane);
  auto const l = magnitude(Vec3f{ 1, 1, 1 });
  REQUIRE(signed_distance(normalized_plane, { 1, 1, 1 }) == Catch::Approx(l));
  REQUIRE(
      signed_distance(normalized_plane, { -1, -1, -1 }) == Catch::Approx(-l));
}

TEST_CASE("intersect_planes")
{
  auto const p1 = Plane{
    { 1, 0, 0 },
    -3
  };
  auto const p2 = Plane{
    { 0, 1, 0 },
    -3
  };
  auto const p3 = Plane{
    { 0, 0, 1 },
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
    { 1, 0, 0 },
    0
  };
  auto const p2 = Plane{
    { 1, 0, 0 },
    1
  };
  auto const p3 = Plane{
    { 1, 0, 0 },
    2
  };
  auto const result = intersection_point(p1, p2, p3);
  REQUIRE(!result.has_value());
}

TEST_CASE("normalized_line_from_line")
{
  auto const dir = Vec3f{ 1, 1, 1 };
  auto const l = magnitude(dir);
  auto const moment = Normal3f{ 1, 1, 1 };
  auto const line = Line{ dir, moment };
  auto const normalized_line = NormalizedLine::from_line(line);
  REQUIRE(magnitude(normalized_line.direction) == Catch::Approx(1.0));
  REQUIRE(magnitude(normalized_line.moment)
          == Catch::Approx(magnitude(moment) / l));
}

TEST_CASE("joint_two_points")
{
  auto const p1 = Point3f{ 1, 0, 1 };
  auto const p2 = Point3f{ 1, 0, 2 };
  auto const result = NormalizedLine::from_line(join(p1, p2));
  auto const expected = NormalizedLine::from_line({
      { 0, 0,  1 },
      { 0, -1, 0 }
  });
  REQUIRE(result == expected);
}

TEST_CASE("join_line_point")
{
  auto const p = Point3f{ 1, 0, 1 };
  auto const l = Line{
    { 0, 0, 1 },
    { 0, 1, 0 }
  };
  auto const result = NormalizedPlane::from_plane(join(l, p));
  auto const expected = NormalizedPlane::from_plane(Plane{
      { 0, 1, 0 },
      0
  });
  REQUIRE(result == expected);
}

TEST_CASE("meet_plane_plane")
{
  auto const p1 = Plane{
    { 1, 0, 0 },
    0
  };
  auto const p2 = Plane{
    { 0, 1, 0 },
    0
  };
  auto const result = NormalizedLine::from_line(meet(p1, p2));
  auto const expected = NormalizedLine::from_line(Line{
      { 0, 0, 1 },
      { 0, 0, 0 }
  });
  REQUIRE(result == expected);
}

TEST_CASE("meet_line_plane")
{
  auto const p = Plane{
    { 0, 0, 1 },
    0
  };
  auto const l = join(Point3f{ 1, 0, 0 }, Point3f{ 1, 0, 1 });
  auto const result = Point3f::project(meet(l, p));
  auto const expected = Point3f{ 1, 0, 0 };
  REQUIRE(result == expected);
}