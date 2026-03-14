#pragma once

#include <numbers>
#include <limits>

#include "gmath/base.hpp"

namespace gmath
{

auto constexpr PI = std::numbers::pi_v<Real>;
auto constexpr INV_PI = 1 / PI;
auto constexpr INFTY = std::numeric_limits<Real>::infinity();

} // namespace gmath
