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
  V unwrap() const
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