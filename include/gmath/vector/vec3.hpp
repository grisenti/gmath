#pragma once

#include "geometric_vector.hpp"
#include "gmath/debug.hpp"

namespace gmath
{

template <typename T>
struct Vec3 : GeometricColumnVectorBase<3, T>
{
  T x;
  T y;
  T z;

  constexpr Vec3() = default;

  constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z)
  {
    GMATH_DEBUG_ASSERT(!contains_nan(*this));
  }

  T const &operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Vec3 must be standard layout for operator[] to work");
    GMATH_DEBUG_ASSERT(i < Vec3::SIZE);
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Vec3 must be standard layout for operator[] to work");
    GMATH_DEBUG_ASSERT(i < Vec3::SIZE);
    return (&x)[i];
  }
};

template <Array A>
  requires(A::SIZE == 3)
Vec3<ComponentT<A>> constexpr as_vec3(A const &a)
{
  return { a[0], a[1], a[2] };
}

using Vec3f = Vec3<Real>;
using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned>;

template <GeometricVector V1, GeometricVector V2>
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

} // namespace gmath