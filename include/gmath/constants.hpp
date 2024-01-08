#pragma once

#include <numbers>
#include <limits>

#include "gmath/base.hpp"

auto constexpr pi = std::numbers::pi_v<Real>;
auto constexpr inf = std::numeric_limits<Real>::infinity();