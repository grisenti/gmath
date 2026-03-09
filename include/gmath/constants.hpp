#pragma once

#include <numbers>
#include <limits>

#include "gmath/base.hpp"

namespace gmath
{

auto constexpr C_PI = std::numbers::pi_v<Real>;
auto constexpr INFTY = std::numeric_limits<Real>::infinity();

} // namespace gmath