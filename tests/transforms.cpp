#include "test.hpp"

#include "transform/transform2D.hpp"

TEST_CASE("Transform2D_rotation")
{
  auto const transform = Transform2D::from_rotation(degf{ 90 });
  auto const v = vec2f{ 1, 0 };
  auto const result = transform * v;
  REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE(result.y == Catch::Approx(1));
}

TEST_CASE("Transform2D_uniform_scale")
{
  auto const transform = Transform2D::from_scale(2.0);
  auto const v = vec2f{ 1, -1 };
  auto const result = transform * v;
  REQUIRE(result == vec2f{ 2, -2 });
}

TEST_CASE("Transform2D_non_uniform_scale")
{
  auto const transform = Transform2D::from_scale({ 2.0, 3.0 });
  auto const v = vec2f{ 1, -1 };
  auto const result = transform * v;
  REQUIRE(result == vec2f{ 2, -3 });
}