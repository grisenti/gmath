#pragma once

#include "vec_base.hpp"

template <typename T>
struct Vec3 : BaseColumnVector<3, T>
{
  T x;
  T y;
  T z;

  Vec3() = default;

  Vec3(T x, T y, T z) : x(x), y(y), z(z)
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Vec3 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Vec3 must be standard layout for operator[] to work");
    return (&x)[i];
  }
};

using Vec3f = Vec3<Real>;
using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned>;

template <Vector V1, Vector V2>
  requires VectorCompatibleWeak<V1, V2> && (V1::SIZE == 3)
Vec3<ComponentT<V1>> constexpr cross(V1 const &lhs, V2 const &rhs)
{
  // clang-format off
  return {
    lhs[1] * rhs[2] - lhs[2] * rhs[1],
    lhs[2] * rhs[0] - lhs[0] * rhs[2],
    lhs[0] * rhs[1] - lhs[1] * rhs[0]
  };
  // clang-format on
}

template <Vector V1, Vector V2, Vector V3>
  requires VectorCompatible<V1, V2> && VectorCompatible<V2, V3>
           && (V1::SIZE == 3)
ComponentT<V1> constexpr scalar_triple_product(
    V1 const &a, V2 const &b, V3 const &c)
{
  return dot(cross(a, b), c);
}
