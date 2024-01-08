#pragma once

#include "base.hpp"
#include <numbers>

template <typename T>
class Unit
{
public:
  constexpr Unit() : _value(0)
  {
  }

  explicit constexpr Unit(T value) : _value(value)
  {
  }

  constexpr T value() const
  {
    return _value;
  }

private:
  T _value;
};

template <typename T>
struct Radians;

template <typename T>
class Degrees : public Unit<T>
{
public:
  constexpr Degrees() = default;

  explicit constexpr Degrees(T value) : Unit<T>(value)
  {
  }

  // NOLINT: degrees and radians can be used interchangeably.
  constexpr Degrees(Radians<T> rad)
      : Unit<T>(rad.value() * T{ 180 } / std::numbers::pi_v<T>)
  {
  }
};

using Degf = Degrees<Real>;

Degf constexpr operator""_deg(long double x)
{
  return Degf(static_cast<Real>(x));
}

Degf constexpr operator""_deg(unsigned long long x)
{
  return Degf(static_cast<Real>(x));
}

template <typename T>
struct Radians : public Unit<T>
{
public:
  constexpr Radians() = default;

  explicit constexpr Radians(T value) : Unit<T>(value)
  {
  }

  // NOLINT: degrees and radians can be used interchangeably.
  constexpr Radians(Degrees<T> deg)
      : Unit<T>(deg.value() * std::numbers::pi_v<T> / T{ 180 })
  {
  }
};

using Radf = Radians<Real>;

Radf constexpr operator""_rad(long double x)
{
  return Degf(static_cast<Real>(x));
}

inline Real sin(Radf rad)
{
  return std::sin(rad.value());
}

inline Real cos(Radf rad)
{
  return std::cos(rad.value());
}

inline Real tan(Radf rad)
{
  return std::tan(rad.value());
}