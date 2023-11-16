#pragma once

#include "base.hpp"
#include <cmath>

/// Marker type for vectors
struct VectorTag
{
};

/// Base class meant to remove duplicated code in the various Vec structs
template <size_t N, typename T>
struct BaseVector
{
  using type_class = VectorTag;
  using value_type = T;
  static constexpr size_t size = N;
};

template <typename V>
concept Vec = requires(V const &cr_vec, V vec) {
  typename V::value_type;
  V::size;
  {
    cr_vec[0]
  } -> std::same_as<typename V::value_type>;
  {
    vec[0]
  } -> std::same_as<typename V::value_type &>;
} && std::same_as<typename V::type_class, VectorTag>;

/// The type of V's components
template <Vec V>
using ComponentT = typename V::value_type;

template <Vec V>
  requires std::equality_comparable<ComponentT<V>>
bool constexpr operator==(V const &lhs, V const &rhs)
{
  auto equal = true;
  for (size_t i = 0; i < V::size; ++i)
    equal = equal && (lhs[i] == rhs[i]);
  return equal;
}

template <Vec V>
V constexpr &operator+=(V &lhs, V const &rhs)
{
  for (size_t i = 0; i < V::size; ++i)
    lhs[i] += rhs[i];
  return lhs;
}

template <Vec V>
V constexpr &operator-=(V &lhs, V const &rhs)
{
  for (size_t i = 0; i < V::size; ++i)
    lhs[i] -= rhs[i];
  return lhs;
}

template <Vec V>
V constexpr &operator*=(V &lhs, ComponentT<V> const k)
{
  for (size_t i = 0; i < V::size; ++i)
    lhs[i] *= k;
  return lhs;
}

template <Vec V>
V constexpr operator-(V const &rhs)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = -rhs[i];
  return ret;
}

template <Vec V>
V constexpr operator*(V const &lhs, ComponentT<V> k)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = lhs[i] * k;
  return ret;
}

template <Vec V>
V constexpr operator*(ComponentT<V> k, V const &rhs)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = rhs[i] * k;
  return ret;
}

template <Vec V>
V constexpr operator/(V const &lhs, ComponentT<V> const k)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = lhs[i] / k;
  return ret;
}

template <Vec V>
V constexpr operator+(V const &lhs, V const &rhs)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = lhs[i] + rhs[i];
  return ret;
}

template <Vec V>
V constexpr operator-(V const &lhs, V const &rhs)
{
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = lhs[i] - rhs[i];
  return ret;
}

template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
ComponentT<V> constexpr length(V const &v)
{
  ComponentT<V> ret = {};
  for (size_t i = 0; i < V::size; ++i)
    ret += pow2(v[i]);
  return std::sqrt(ret);
}

template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
ComponentT<V> constexpr distance(V const &lhs, V const &rhs)
{
  ComponentT<V> ret = {};
  for (size_t i = 0; i < V::size; ++i)
    ret += pow2(lhs[i] - rhs[i]);
  return std::sqrt(ret);
}

template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
V constexpr normalize(V const &v)
{
  auto const l = length(v);
  V ret;
  for (size_t i = 0; i < V::size; ++i)
    ret[i] = v[i] / l;
  return ret;
}

template <Vec V>
ComponentT<V> constexpr dot(V const &lhs, V const &rhs)
{
  ComponentT<V> ret{ 0 };
  for (size_t i = 0; i < V::size; ++i)
    ret += lhs[i] * rhs[i];
  return ret;
}

template <Vec V>
bool constexpr in_range(V const &v, V const &a, V const &b)
{
  bool ret = true;
  for (size_t i = 0; i < V::size; ++i)
    ret = ret && in_range(v[i], a[i], b[i]);
  return ret;
}

template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
V project(V const &a, V const &b)
{
  return b * (dot(a, b) / dot(b, b));
}

template <Vec V>
V project_no_division(V const &a, V const &b)
{
  return b * (dot(a, b));
}

template <Vec V>
  requires(std::floating_point<ComponentT<V>>)
V reject(V const &a, V const &b)
{
  return a - project(a, b);
}

template <Vec V>
V reject_no_division(V const &a, V const &b)
{
  return a - project_no_division(a, b);
}
