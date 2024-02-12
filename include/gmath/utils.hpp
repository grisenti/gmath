#pragma once

#include "gmath/base.hpp"

namespace gmath
{

template <Numeric T>
constexpr T pow2(T const x)
{
  return x * x;
}

template <Numeric T>
constexpr T clamp(T const x, T const a, T const b)
{
  if (x < a)
    return a;
  if (x > b)
    return b;
  return x;
}

} // namespace gmath