#pragma once

#include "vec_base.hpp"

template <typename T>
struct Vec4 : BaseVector<4, T>
{
  T x;
  T y;
  T z;
  T w;

  Vec4() = default;

  Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
  {
  }

  template <Vector V>
    requires(V::SIZE == 4) && std::same_as<ComponentT<V>, T>
  Vec4(V const &v) : x(v[0]), y(v[1]), z(v[2]), w(v[3])
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Vec4<T>>,
        "Vec4 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Vec4<T>>,
        "Vec4 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  template <Vector V>
    requires(V::SIZE == 4) && std::same_as<ComponentT<V>, T>
  operator V() const
  {
    return { x, y, z, w };
  }
};

using Vec4f = Vec4<Real>;
using Vec4i = Vec4<int>;
using Vec4u = Vec4<unsigned>;
