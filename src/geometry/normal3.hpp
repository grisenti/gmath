#pragma once

#include "vector/vec3.hpp"

struct NormalTag : RowVectorTag
{
};

template <typename T>
struct Normal3
{
  using TypeClass = NormalTag;
  using ComponentType = T;
  static constexpr size_t SIZE = 3;

  T x;
  T y;
  T z;

  static Normal3 cross(Vec3<T> const &lhs, Vec3<T> const &rhs)
  {
    return ::cross(lhs, rhs);
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

  Vec3<T> const &as_vec3() const
  {
    static_assert(std::is_standard_layout_v<Vec3<T>>,
        "Vec3 must be standard layout for Normal3::as_vec3() to work");
    static_assert(std::is_standard_layout_v<Normal3<T>>,
        "Normal3 must be standard layout for Normal3::as_vec3() to work");

    return reinterpret_cast<Vec3<T> const &>(*this);
  }
};

using Normal3f = Normal3<Real>;

template <typename T, Vector V>
  requires std::is_same_v<T, ComponentT<V>> && (V::SIZE == 3)
ComponentT<V> dot(Normal3<T> const &lhs, V const &rhs)
{
  return dot(lhs.as_vec3(), rhs);
}

template <typename T, Vector V>
  requires std::is_same_v<T, ComponentT<V>> && (V::SIZE == 3)
ComponentT<V> dot(V const &lhs, Normal3<T> const &rhs)
{
  return dot(lhs, rhs.as_vec3());
}

template <typename T, Vector V>
  requires std::is_same_v<T, ComponentT<V>> && (V::SIZE == 3)
ComponentT<V> cross(Normal3<T> const &lhs, V const &rhs)
{
  return cross(lhs.as_vec3(), rhs);
}

template <typename T, Vector V>
  requires std::is_same_v<T, ComponentT<V>> && (V::SIZE == 3)
ComponentT<V> cross(V const &lhs, Normal3<T> const &rhs)
{
  return cross(lhs, rhs.as_vec3());
}
