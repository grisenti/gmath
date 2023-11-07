#include "test.hpp"

#include "units.hpp"

TEST_CASE("degrees_to_radians")
{
  auto const deg = degf{ 180 };
  auto const expected = radf{ std::numbers::pi_v<float> };
  auto const result = radf{ deg };
  REQUIRE(result.value() == Catch::Approx(expected.value()));
}

TEST_CASE("radians_to_degrees")
{
  auto const rad = radf{ std::numbers::pi_v<float> };
  auto const expected = degf{ 180 };
  auto const result = degf{ rad };
  REQUIRE(result.value() == Catch::Approx(expected.value()));
}