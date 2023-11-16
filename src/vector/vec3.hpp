#pragma once

#include "vec_base.hpp"

template <typename T>
struct Vec3 : BaseVector<3, T>
{
  T x;
  T y;
  T z;

  Vec3() = default;

  Vec3(T x, T y, T z) : x(x), y(y), z(z)
  {
  }

  template <Vec V>
    requires(V::size == 3) && std::same_as<ComponentT<V>, T>
  Vec3(V const &v) : x(v[0]), y(v[1]), z(v[2])
  {
  }

  T operator[](size_t i) const
  {
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    return (&x)[i];
  }

  template <Vec V>
    requires(V::size == 3) && std::same_as<ComponentT<V>, T>
  operator V() const
  {
    return { x, y, z };
  }
};

using vec3f = Vec3<float>;
using vec3i = Vec3<int>;
using vec3u = Vec3<unsigned>;

template <Vec V>
  requires Numeric<ComponentT<V>> && (V::size == 3)
V constexpr cross(V const &lhs, V const &rhs)
{
  // clang-format off
  return {
    lhs[1] * rhs[2] - lhs[2] * rhs[1],
    lhs[2] * rhs[0] - lhs[0] * rhs[2],
    lhs[0] * rhs[1] - lhs[1] * rhs[0]
  };
  // clang-format on
}

template <Vec V>
  requires Numeric<ComponentT<V>> && (V::size == 3)
V constexpr scalar_triple_product(V const &a, V const &b, V const &c)
{
  return dot(cross(a, b), c);
}
