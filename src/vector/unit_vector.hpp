#pragma once

#include "vec_base.hpp"

/// Type safe wrapper for a unit vector.
template <Vec V>
  requires(std::floating_point<ElemT<V>>)
class UnitVec
{
public:
  /// Creates a UnitVec assuming v is already normalized.
  static UnitVec create_unchecked(V const &v)
  {
    return { v };
  }

  // NOLINT: implicit conversion is intended (makes passing a standard Vec
  // to a function expecting a unit vector simple).
  UnitVec(V const &v) : value(normalize(v))
  {
  }

  // NOLINT: implicit conversion is intended. A UnitVec can be used everywhere
  // a standard Vec can.
  operator V() const
  {
    return value;
  }

  /// @returns The underlying normalized vector.
  V unwrap() const
  {
    return value;
  }

private:
  // invariant: the value is always normalized.
  V value;
};