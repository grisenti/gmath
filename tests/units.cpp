#include "test.hpp"

#include "gmath/units.hpp"

TEST_CASE("degrees_to_radians")
{
  auto const deg = Degf{ 180 };
  auto const expected = Radf{ std::numbers::pi_v<float> };
  auto const result = Radf{ deg };
  REQUIRE(result.value() == Catch::Approx(expected.value()));
}

TEST_CASE("radians_to_degrees")
{
  auto const rad = Radf{ std::numbers::pi_v<float> };
  auto const expected = Degf{ 180 };
  auto const result = Degf{ rad };
  REQUIRE(result.value() == Catch::Approx(expected.value()));
}