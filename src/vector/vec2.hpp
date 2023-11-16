#pragma once

#include "vec_base.hpp"
#include "vecn.hpp"

template <typename T>
struct Vec2 : BaseVector<2, T>
{
  T x;
  T y;

  Vec2() = default;

  Vec2(T x, T y) : x(x), y(y)
  {
  }

  template <Vec V>
    requires(V::size == 2) && std::same_as<ComponentT<V>, T>
  Vec2(V const &v) : x(v[0]), y(v[1])
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
    requires(V::size == 2) && std::same_as<ComponentT<V>, T>
  operator V() const
  {
    return { x, y };
  }
};

using vec2f = Vec2<float>;
using vec2i = Vec2<int>;
using vec2u = Vec2<unsigned>;
