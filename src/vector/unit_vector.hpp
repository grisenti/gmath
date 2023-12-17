#pragma once

#include "vec_base.hpp"

/// Type safe wrapper for a unit vector.
template <Vector V>
  requires(std::floating_point<ComponentT<V>>)
class UnitVec
{
public:
  using TypeClass = typename V::TypeClass;
  using ComponentType = ComponentT<V>;
  static constexpr size_t SIZE = V::SIZE;
  using ModifiableEquivalent = V;

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
  // a standard Vector can.
  operator V() const
  {
    return _value;
  }

  /// @returns The underlying normalized vector.
  V const &unwrap() const
  {
    return _value;
  }

  ComponentType operator[](size_t i) const
  {
    return _value[i];
  }

private:
  UnitVec(V const &v) : _value{ v }
  {
  }

  // invariant: the value is always normalized.
  V _value;
};

template <Vector V>
UnitVec<V> operator-(UnitVec<V> const &v)
{
  // negating a unit vector does not change its length
  return UnitVec<V>::create_unchecked(-v.unwrap());
}