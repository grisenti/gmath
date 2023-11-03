#pragma once

#include "vec_base.hpp"

template <typename T>
struct Vec4
{
  using value_type = T;
  static constexpr size_t size = 4;

  T x;
  T y;
  T z;
  T w;

  Vec4() = default;

  Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
  {
  }

  template <Vec V>
    requires(V::size == 4) && std::same_as<ElemT<V>, T>
  Vec4(V const &v) : x(v[0]), y(v[1]), z(v[2]), w(v[3])
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
    requires(V::size == 4) && std::same_as<ElemT<V>, T>
  operator V() const
  {
    return { x, y, z, w };
  }
};

using vec4f = Vec4<float>;
using vec4i = Vec4<int>;
using vec4u = Vec4<unsigned>;
