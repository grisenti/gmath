#pragma once

#include "gmath/base.hpp"

template <Numeric T>
T pow2(T const x)
{
  return x * x;
}

template <Numeric T>
T constexpr clamp(T const x, T const a, T const b)
{
  if (x < a)
    return a;
  if (x > b)
    return b;
  return x;
}