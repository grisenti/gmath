#pragma once

#include <cmath>

#include "array.hpp"

namespace gmath
{

template <Numeric T>
constexpr bool contains_nan(T v)
{
  return std::isnan(v);
}

template <Array A>
constexpr bool contains_nan(A const &a)
{
  for (size_t i = 0; i < A::SIZE; ++i)
    if (contains_nan(a[i]))
      return true;
  return false;
}

template <Numeric T>
constexpr bool contains_inf(T v)
{
  return std::isinf(v);
}

template <Array A>
constexpr bool contains_inf(A const &a)
{
  for (size_t i = 0; i < A::SIZE; ++i)
    if (contains_inf(a[i]))
      return true;
  return false;
}

}

#ifndef GMATH_DEBUG

#ifndef GMATH_DEBUG_ASSERT
#include <cassert>

#define GMATH_DEBUG_ASSERT(x) assert(x)
#endif // GMATH_DEBUG_ASSERT

#else

#ifndef GMATH_DEBUG_ASSERT
#define GMATH_DEBUG_ASSERT(x)
#endif // GMATH_DEBUG_ASSERT

#endif // GMATH_DEBUG