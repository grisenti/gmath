#pragma once

#include "matrix/matrix_base.hpp"
#include "vector/vec2.hpp"
#include "vector/vec3.hpp"
#include "vector/vec4.hpp"
#include "vector/vecn.hpp"

struct PointTag : ColumnMatrixTag
{
};

template <size_t N, typename T>
struct PointBase
{
  using TypeClass = PointTag;
  using ComponentType = T;
  static constexpr size_t SIZE = N;

  bool operator<=>(PointBase const &rhs) const = default;
};

template <typename P>
concept Point = ModifiableMatrix1D<P>
                && std::is_base_of_v<PointTag, typename P::TypeClass>;

template <typename T>
struct Point2 : PointBase<2, T>
{
  T x;
  T y;

  Point2() = default;

  Point2(T x, T y) : x(x), y(y)
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Point2<T>>,
        "Point2 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Point2<T>>,
        "Point2 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  bool operator<=>(Point2 const &rhs) const = default;
};

using Point2f = Point2<Real>;
using Point2i = Point2<int>;

template <typename T>
struct Point3 : PointBase<3, T>
{
  T x;
  T y;
  T z;

  static Point3<T> from_vec3(Vec3<T> const &v)
  {
    return { v.x, v.y, v.z };
  }

  Point3() = default;

  Point3(T x, T y, T z) : x(x), y(y), z(z)
  {
  }

  T operator[](size_t i) const
  {
    static_assert(std::is_standard_layout_v<Point3<T>>,
        "Point3 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  T &operator[](size_t i)
  {
    static_assert(std::is_standard_layout_v<Point3<T>>,
        "Point3 must be standard layout for operator[] to work");
    return (&x)[i];
  }

  bool operator<=>(Point3 const &rhs) const = default;
};

template <typename T>
Vec3<T> constexpr as_vec3(Point3<T> const &p)
{
  return Vec3<T>{ p.x, p.y, p.z };
}

template <typename T>
Vec4<T> constexpr as_vec4(Point3<T> const &p)
{
  return Vec4<T>{ p.x, p.y, p.z, 1 };
}

using Point3f = Point3<Real>;
using Point3i = Point3<int>;

template <Point P, Vector V>
  requires(P::SIZE == V::SIZE) && std::same_as<ComponentT<P>, ComponentT<V>>
P operator+(P const &lhs, V const &rhs)
{
  auto res = P{};
  for (size_t i = 0; i < P::SIZE; ++i)
    res[i] = lhs[i] + rhs[i];
  return res;
}

template <Point P, Vector V>
  requires(P::SIZE == V::SIZE) && std::same_as<ComponentT<P>, ComponentT<V>>
P operator-(P const &lhs, V const &rhs)
{
  auto res = P{};
  for (size_t i = 0; i < P::SIZE; ++i)
    res[i] = lhs[i] - rhs[i];
  return res;
}

template <Point P, Vector V>
  requires(P::SIZE == V::SIZE) && std::same_as<ComponentT<P>, ComponentT<V>>
P &operator+=(P &lhs, V const &rhs)
{
  for (size_t i = 0; i < P::SIZE; ++i)
    lhs[i] += rhs[i];
  return lhs;
}

template <Point P>
VectorOf<P::SIZE, ComponentT<P>> operator-(P const &lhs, P const &rhs)
{
  auto res = VectorOf<P::SIZE, ComponentT<P>>{};
  for (size_t i = 0; i < P::SIZE; ++i)
    res[i] = lhs[i] - rhs[i];
  return res;
}