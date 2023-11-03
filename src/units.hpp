#pragma once

#include "base.hpp"
#include <numbers>

template <typename T>
struct Radians;

template <typename T>
struct Degrees
{
  T value;

  explicit Degrees(T value) : value(value)
  {
  }

  // NOLINT: degrees and radians can be used interchangeably.
  constexpr Degrees(Radians<T> rad)
      : value(rad.value * T{ 180 } / std::numbers::pi_v<T>)
  {
  }
};

using degf = Degrees<float>;

template <typename T>
struct Radians
{
  T value;

  explicit Radians(T value) : value(value)
  {
  }

  // NOLINT: degrees and radians can be used interchangeably.
  constexpr Radians(Degrees<T> deg)
      : value(deg.value * std::numbers::pi_v<T> / T{ 180 })
  {
  }
};

using radf = Radians<float>;