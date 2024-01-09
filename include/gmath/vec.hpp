#pragma once

#include "vector/vec_base.hpp"
#include "vector/vec2.hpp"
#include "vector/vec3.hpp"
#include "vector/vec4.hpp"
#include "vector/vecn.hpp"
#include "vector/unit_vector.hpp"
#include "vector/octahedral_vector.hpp"

namespace gmath
{

template <typename T>
Vec3<T> extend(Vec2<T> const &v, T z = {})
{
  return { v.x, v.y, z };
}

template <typename T>
Vec2<T> truncate(Vec3<T> const &v)
{
  return { v.x, v.y };
}

template <typename T>
Vec4<T> extend(Vec3<T> const &v, T w = {})
{
  return { v.x, v.y, v.z, w };
}

template <typename T>
Vec3<T> truncate(Vec4<T> const &v)
{
  return { v.x, v.y, v.z };
}

template <typename T>
VecN<5, T> extend(Vec4<T> const &v, T value = {})
{
  return { v.x, v.y, v.z, v.w, value };
}

template <typename T>
Vec4<T> truncate(VecN<5, T> const &v)
{
  return { v[0], v[1], v[2], v[3] };
}

template <typename T, size_t N>
VecN<N + 1, T> extend(VecN<N, T> const &v, T value = {})
{
  VecN<N + 1, T> res;
  for (size_t i = 0; i < N; ++i)
    res[i] = v[i];
  res[N] = value;
  return res;
}

template <typename T, size_t N>
  requires(N > 1)
VecN<N - 1, T> truncate(VecN<N, T> const &v)
{
  VecN<N - 1, T> res;
  for (size_t i = 0; i < N - 1; ++i)
    res[i] = v[i];
  return res;
}

using UVec2f = UnitVec<Vec2f>;
using UVec3f = UnitVec<Vec3f>;
using UVec4f = UnitVec<Vec4f>;

static UVec3f constexpr X3f = UVec3f::create_unchecked(1, 0, 0);
static UVec3f constexpr Y3f = UVec3f::create_unchecked(0, 1, 0);
static UVec3f constexpr Z3f = UVec3f::create_unchecked(0, 0, 1);

} // namespace gmath
