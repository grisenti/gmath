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

  T operator[](size_t i) const
  {
    return values[i];
  }

  T &operator[](size_t i)
  {
    return values[i];
  }
};

template <size_t N, typename T>
struct VectorOfT
{
  using Type = VecN<N, T>;
};

template <typename T>
struct VectorOfT<2, T>
{
  using Type = Vec2<T>;
};

template <typename T>
struct VectorOfT<3, T>
{
  using Type = Vec3<T>;
};

template <typename T>
struct VectorOfT<4, T>
{
  using Type = Vec4<T>;
};

template <size_t N, typename T>
using VectorOf = VectorOfT<N, T>::Type;

} // namespace gmath
