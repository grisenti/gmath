#pragma once

#include "gmath/vector/vec_base.hpp"
#include "gmath/debug.hpp"

namespace gmath
{

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
  static UnitVec constexpr create_unchecked(auto &&...args)
  {
    return UnitVec{ V(std::forward<decltype(args)>(args)...) };
  }

  /// creates a UnitVec from the given values, ensuring that the underlying
  /// vector is normalized.
  static UnitVec constexpr normalize(auto &&...args)
  {
    return UnitVec{ ::gmath::normalize(
        V(std::forward<decltype(args)>(args)...)) };
  }

  // NOLINT: implicit conversion is intended. A UnitVec can be used everywhere
  // a standard Vector can.
  constexpr operator V() const
  {
    return _value;
  }

  /// @returns The underlying normalized vector.
  V const &unwrap() const
  {
    return _value;
  }

  ComponentType const &operator[](size_t i) const
  {
    return _value[i];
  }

private:
  constexpr UnitVec(V const &v) : _value{ v }
  {
    GMATH_DEBUG_ASSERT(std::abs(magnitude(v) - 1._r) < 1e-6_r);
  }

  // invariant: the value is always normalized.
  V _value;
};

template <Vector V>
UnitVec<V> constexpr operator-(UnitVec<V> const &v)
{
  // negating a unit vector does not change its absolute magnitude
  return UnitVec<V>::create_unchecked(-v.unwrap());
}

template <GeometricVector V>
auto project(V const &a, UnitVec<V> const &b)
{
  return b * dot(a, b);
}

template <GeometricVector V>
auto reject(V const &a, UnitVec<V> const &b)
{
  return a - project(a, b);
}

template <Vector V>
ComponentT<V> cos_theta(UnitVec<V> const &lhs, UnitVec<V> const &rhs)
{
  return dot(lhs, rhs);
}

} // namespace gmath