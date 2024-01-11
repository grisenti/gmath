#pragma once

#include "gmath/matrix/matrix_base.hpp"
#include "gmath/vector/vec4.hpp"
#include "gmath/vector/vecn.hpp"

namespace gmath
{

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

  constexpr Point2() = default;

  constexpr Point2(T x, T y) : x(x), y(y)
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

template <Matrix1D M>
  requires(M::SIZE == 2)
Point2<ComponentT<M>> constexpr as_point2(M const &m)
{
  return { m[0], m[1] };
}

template <typename T>
struct Point3 : PointBase<3, T>
{
  T x;
  T y;
  T z;

  static Point3 project(Vec4<T> const &v)
  {
    return Point3<T>{ v.x / v.w, v.y / v.w, v.z / v.w };
  }

  constexpr Point3() = default;

  constexpr Point3(T x, T y, T z) : x(x), y(y), z(z)
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

template <Matrix1D M>
  requires(M::SIZE == 3)
Point3<ComponentT<M>> constexpr as_point3(M const &m)
{
  return { m[0], m[1], m[2] };
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
DefaultVectorOf<P::SIZE, ComponentT<P>> operator-(P const &lhs, P const &rhs)
{
  auto res = DefaultVectorOf<P::SIZE, ComponentT<P>>{};
  for (size_t i = 0; i < P::SIZE; ++i)
    res[i] = lhs[i] - rhs[i];
  return res;
}

template <Point P>
ComponentT<P> distance(P const &lhs, P const &rhs)
{
  return magnitude(lhs - rhs);
}

} // namespace gmath
