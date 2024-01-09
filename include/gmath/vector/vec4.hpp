#pragma once

#include "vec_base.hpp"

namespace gmath
{

template <typename T>
struct Vec4 : BaseColumnVector<4, T>
{
  T x;
  T y;
  T z;
  T w;

  constexpr Vec4() = default;

  constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
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
};

using Vec4f = Vec4<Real>;
using Vec4i = Vec4<int>;
using Vec4u = Vec4<unsigned>;

} // namespace gmath