#pragma once

#include "vec_base.hpp"

/// Type safe wrapper for a unit vector.
template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
class UnitVec
{
public:
  /// Creates a UnitVec assuming v is already normalized.
  static UnitVec create_unchecked(auto &&...args)
  {
    return UnitVec{ V(std::forward<decltype(args)>(args)...) };
  }

  /// creates a UnitVec from the given values, ensuring that the underlying
  /// vector is normalized.
  static UnitVec normalize(auto &&...args)
  {
    return UnitVec{ ::normalize(V(std::forward<decltype(args)>(args)...)) };
  }

  // NOLINT: implicit conversion is intended. A UnitVec can be used everywhere
  // a standard Vec can.
  operator V() const
  {
    return _value;
  }

  /// @returns The underlying normalized vector.
  V const &unwrap() const
  {
    return _value;
  }

private:
  UnitVec(V const &v) : _value{ v }
  {
  }

  // invariant: the value is always normalized.
  V _value;
};

template <Vec V>
UnitVec<V> constexpr operator-(UnitVec<V> const &rhs)
{
  return UnitVec<V>::create_unchecked(-rhs.unwrap());
}

template <Vec V>
auto constexpr operator+(UnitVec<V> const &lhs, V const &rhs)
{
  return lhs.unwrap() + rhs;
}

template <Vec V>
auto constexpr operator+(V const &lhs, UnitVec<V> const &rhs)
{
  return lhs + rhs.unwrap();
}

template <Vec V>
auto constexpr operator+(UnitVec<V> const &lhs, UnitVec<V> const &rhs)
{
  return lhs.unwrap() + rhs.unwrap();
}

template <Vec V>
V constexpr operator-(UnitVec<V> const &lhs, V const &rhs)
{
  return lhs.unwrap() - rhs;
}

template <Vec V>
V constexpr operator-(V const &lhs, UnitVec<V> const &rhs)
{
  return lhs - rhs.unwrap();
}

template <Vec V>
V constexpr operator-(UnitVec<V> const &lhs, UnitVec<V> const &rhs)
{
  return lhs.unwrap() - rhs.unwrap();
}

template <Vec V>
ComponentT<V> constexpr dot(V const &lhs, UnitVec<V> const &rhs)
{
  return dot(lhs, rhs.unwrap());
}

template <Vec V>
ComponentT<V> constexpr dot(UnitVec<V> const &lhs, V const &rhs)
{
  return dot(lhs.unwrap(), rhs);
}

template <Vec V>
ComponentT<V> constexpr dot(UnitVec<V> const &lhs, UnitVec<V> const &rhs)
{
  return dot(lhs.unwrap(), rhs.unwrap());
}

template <Vec V>
V project(V const &a, UnitVec<V> const &b)
{
  return project_no_division(a, b.unwrap());
}

template <Vec V>
V reject(V const &a, UnitVec<V> const &b)
{
  return reject_no_division(a, b.unwrap());
}