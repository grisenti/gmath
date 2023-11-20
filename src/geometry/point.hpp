#pragma once

#include "vector/vec_base.hpp"
#include "vector/vec2.hpp"
#include "vector/vec3.hpp"

template <typename T>
struct Point2
{
  T x;
  T y;

  bool operator<=>(Point2 const &rhs) const = default;
};

using Point2f = Point2<Real>;
using Point2i = Point2<int>;

template <typename T>
Vec2<T> operator-(Point2<T> const &lhs, Point2<T> const &rhs)
{
  return Vec2<T>{ lhs.x - rhs.x, lhs.y - rhs.y };
}

template <typename T>
Point2<T> operator+(Point2<T> const &lhs, Vec2<T> const &rhs)
{
  return Point2<T>{ lhs.x + rhs.x, lhs.y + rhs.y };
}

template <typename T>
struct Point3
{
  T x;
  T y;
  T z;

  bool operator<=>(Point3 const &rhs) const = default;
};

using Point3f = Point3<Real>;
using Point3i = Point3<int>;

template <typename T>
Vec3<T> operator-(Point3<T> const &lhs, Point3<T> const &rhs)
{
  return Vec3<T>{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

template <typename T>
Point3<T> operator+(Point3<T> const &lhs, Vec3<T> const &rhs)
{
  return Point3<T>{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}