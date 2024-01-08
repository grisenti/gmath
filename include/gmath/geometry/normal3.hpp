#pragma once

#include "gmath/vector/vec3.hpp"

struct NormalTag : RowVectorTag
{
};

template <typename N>
concept Normal
    = RowVector<N> && std::derived_from<typename N::TypeClass, NormalTag>;

template <typename T>
struct Normal3
{
  using TypeClass = NormalTag;
  using ComponentType = T;
  static constexpr size_t SIZE = 3;

  T x;
  T y;
  T z;

  template <Vector V1, Vector V2>
  requires VectorCompatibleWeak<V1, V2> && std::same_as<ComponentT<V1>, T> &&(
      V1::SIZE == 3) static Normal3 cross(V1 const &lhs, V2 const &rhs)
  {
    return Normal3{ ::cross(lhs, rhs) };
  }

  Normal3() = default;

  explicit Normal3(Vec3<T> const &v) : x(v.x), y(v.y), z(v.z)
  {
  }

  Normal3(T x, T y, T z) : x(x), y(y), z(z)
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Normal3 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Normal3 must be standard layout for operator[] to work");
    return (&x)[i];
  }
};

using Normal3f = Normal3<Real>;

template <typename T>
Vec3<T> as_vec3(Normal3<T> const &n)
{
  return { n.x, n.y, n.z };
}

template <Vector V1, Vector V2>
requires(Normal<V1> || Normal<V2>)
    && VectorCompatibleWeak<V1, V2> ComponentT<V1> dot(
        V1 const &lhs, V2 const &rhs)
{
  return weak_dot(lhs, rhs);
}