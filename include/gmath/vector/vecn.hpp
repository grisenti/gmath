#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace gmath
{

template <size_t N, typename T>
struct VecN
{
  using TypeClass = ColumnVectorTag;
  using ComponentType = T;
  static constexpr size_t SIZE = N;

  T values[N];

  T const &operator[](size_t i) const
  {
    return values[i];
  }

  T &operator[](size_t i)
  {
    return values[i];
  }
};

template <Array A>
VecN<A::SIZE, ComponentT<A>> constexpr as_vecn(A const &a)
{
  VecN<A::SIZE, ComponentT<A>> res;
  for (size_t i = 0; i < A::SIZE; ++i)
    res[i] = a[i];
  return res;
}

template <size_t N, typename T>
struct DefaultVectorOfT
{
  using Type = VecN<N, T>;
};

template <typename T>
struct DefaultVectorOfT<2, T>
{
  using Type = Vec2<T>;
};

template <typename T>
struct DefaultVectorOfT<3, T>
{
  using Type = Vec3<T>;
};

template <typename T>
struct DefaultVectorOfT<4, T>
{
  using Type = Vec4<T>;
};

template <size_t N, typename T>
using DefaultVectorOf = DefaultVectorOfT<N, T>::Type;

} // namespace gmath
