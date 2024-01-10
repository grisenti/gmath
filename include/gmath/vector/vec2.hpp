#pragma once

#include "geometric_vector.hpp"

namespace gmath
{

template <typename T>
struct Vec2 : GeometricColumnVectorBase<2, T>
{
  T x;
  T y;

  constexpr Vec2() = default;

  constexpr Vec2(T x, T y) : x(x), y(y)
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
};

template <Array A>
  requires(A::SIZE == 2)
Vec2<ComponentT<A>> constexpr as_vec2(A const &a)
{
  return { a[0], a[1] };
}

using Vec2f = Vec2<Real>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;

} // namespace gmath
