#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

template <size_t N, typename T>
struct VecN
{
  using type_class = VectorTag;
  using component_type = T;
  static constexpr size_t size = N;

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
  using type = VecN<N, T>;
};

template <typename T>
struct VectorOfT<2, T>
{
  using type = Vec2<T>;
};

template <typename T>
struct VectorOfT<3, T>
{
  using type = Vec3<T>;
};

template <typename T>
struct VectorOfT<4, T>
{
  using type = Vec4<T>;
};

template <size_t N, typename T>
using VectorOf = VectorOfT<N, T>::type;