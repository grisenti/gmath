#pragma once

#include <concepts>
#include <cstddef>

template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

using std::size_t;

using Real = float;

Real constexpr operator""_r(long double x)
{
  return static_cast<Real>(x);
}

template <Numeric T>
T pow2(T const x)
{
  return x * x;
}
