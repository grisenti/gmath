#include "test.hpp"

#include "gmath/numeric_utils.hpp"
#include <algorithm>

TEST_CASE("pow2")
{
  REQUIRE(pow2(3) == 9);
}

TEST_CASE("clamp")
{
  REQUIRE(clamp(30, 4, 8) == 8);
  REQUIRE(clamp(-30, 4, 8) == 4);
  REQUIRE(clamp(6, 4, 8) == 6);
}

TEST_CASE("wrapping add")
{
  REQUIRE(wrapping_add(10, 1, 3, 11) == 3);
  REQUIRE(wrapping_add(1, 10, 3, 11) == 3);
  REQUIRE(wrapping_add(4, 1, 3, 11) == 5);
}