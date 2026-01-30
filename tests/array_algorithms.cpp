#include "test.hpp"

#include "gmath/array_algorithms.hpp"
#include "gmath/vec.hpp"

TEST_CASE("max component index")
{
  auto const v1 = Vec3i{ 1, 2, 3 };
  REQUIRE(max_component_index(v1) == 2);

  auto const v2 = Vec3i{ 3, 0, 0 };
  REQUIRE(max_component_index(v2) == 0);

  auto const v3 = Vec3i{ 0, 10, 0 };
  REQUIRE(max_component_index(v3) == 1);

  auto const v4 = Vec3i{ 1, 1, 1 };
  REQUIRE(max_component_index(v4) == 0);
}

TEST_CASE("min_component_index")
{
  auto const v1 = Vec3i{ 1, 2, 3 };
  REQUIRE(min_component_index(v1) == 0);

  auto const v2 = Vec3i{ 1, 3, -1 };
  REQUIRE(min_component_index(v2) == 2);

  auto const v3 = Vec3i{ 0, -10, 0 };
  REQUIRE(min_component_index(v3) == 1);

  auto const v4 = Vec3i{ 1, 1, 1 };
  REQUIRE(min_component_index(v4) == 0);
}

TEST_CASE("permute")
{
  auto const v = Vec3i{ 1, 2, 3 };
  REQUIRE(permute(v, { 2, 0, 1 }) == Vec3i{ 3, 1, 2 });
}

TEST_CASE("abs")
{
  auto const v = Vec3i{ 1, -2, 3 };
  REQUIRE(abs(v) == Vec3i{ 1, 2, 3 });

  auto const v2 = Vec3<Vec3i>{
    { 1,  -2, 3 },
    { 1,  2,  3 },
    { -1, -2, 3 }
  };
  auto const v2_abs = Vec3<Vec3i>{
    { 1, 2, 3 },
    { 1, 2, 3 },
    { 1, 2, 3 }
  };
  REQUIRE(abs(v2) == v2_abs);
}

TEST_CASE("componentwise_mul")
{
  auto const v1 = Vec3i{ 1, 1, 1 };
  auto const v2 = Vec3i{ 2, 3, 4 };
  auto const res = componentwise_mul(v1, v2);
  REQUIRE(res == Vec3i{2, 3, 4});
}

TEST_CASE("componentwise_div")
{
  auto const v1 = Vec3i{ 4, 6, 20 };
  auto const v2 = Vec3i{ 2, 3, 4 };
  auto const res = componentwise_div(v1, v2);
  REQUIRE(res == Vec3i{2, 2, 5});
}