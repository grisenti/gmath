#pragma once

#include "vec_base.hpp"

template <typename T>
struct Vec2 : BaseVector<2, T>
{
  T x;
  T y;

  Vec2() = default;

  Vec2(T x, T y) : x(x), y(y)
  {
  }

  template <Vector V>
    requires(V::SIZE == 2) && std::same_as<ComponentT<V>, T>
  Vec2(V const &v) : x(v[0]), y(v[1])
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Vec2<T>>,
        "Vec2 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Vec2<T>>,
        "Vec2 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  template <Vector V>
    requires(V::SIZE == 2) && std::same_as<ComponentT<V>, T>
  operator V() const
  {
    return { x, y };
  }
};

using Vec2f = Vec2<Real>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;
