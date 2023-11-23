#pragma once

#include "base.hpp"
#include "matrix/matrix_base.hpp"
#include <cmath>

/// Marker type for column vectors
struct ColumnVectorTag : ColumnMatrixTag
{
};

/// Base class meant to remove duplicated code in the various Vector structs
template <size_t N, typename T>
struct BaseColumnVector
{
  using TypeClass = ColumnVectorTag;
  using ComponentType = T;
  static constexpr size_t SIZE = N;
};

/// Marker type for row vectors
struct RowVectorTag : RowMatrixTag
{
};

template <typename V>
concept ModifiableColumnVector
    = ModifiableColumnMatrix<V>
      && std::derived_from<typename V::TypeClass, ColumnVectorTag>;

template <typename V>
concept ConstColumnVector
    = ConstColumnMatrix<V>
      && std::derived_from<typename V::TypeClass, ColumnVectorTag>;

template <typename V>
concept ModifiableRowVector
    = ModifiableRowMatrix<V>
      && std::derived_from<typename V::TypeClass, RowVectorTag>;

template <typename V>
concept ConstRowVector
    = ConstRowMatrix<V>
      && std::derived_from<typename V::TypeClass, RowVectorTag>;

template <typename V>
concept ModifiableVector = ModifiableColumnVector<V> || ModifiableRowVector<V>;

template <typename V>
concept ConstVector = ConstColumnVector<V> || ConstRowVector<V>;

template <typename V>
concept Vector = ModifiableVector<V> || ConstVector<V>;

template <typename V1, typename V2>
concept VectorCompatible
    = Vector<V1> && Vector<V2> && std::same_as<ComponentT<V1>, ComponentT<V2>>
      && (V1::SIZE == V2::SIZE)
      && std::same_as<typename V1::TypeClass, typename V2::TypeClass>
      && std::same_as<ModifiableEquivalentT<V1>, ModifiableEquivalentT<V2>>;

template <Vector V>
  requires std::equality_comparable<ComponentT<V>>
bool constexpr operator==(V const &lhs, V const &rhs)
{
  auto equal = true;
  for (size_t i = 0; i < V::SIZE; ++i)
    equal = equal && (lhs[i] == rhs[i]);
  return equal;
}

template <ModifiableVector V1, Vector V2>
  requires VectorCompatible<V1, V2>
V1 constexpr &operator+=(V1 &lhs, V2 const &rhs)
{
  for (size_t i = 0; i < V1::SIZE; ++i)
    lhs[i] += rhs[i];
  return lhs;
}

template <ModifiableVector V1, Vector V2>
  requires VectorCompatible<V1, V2>
V1 constexpr &operator-=(V1 &lhs, V2 const &rhs)
{
  for (size_t i = 0; i < V1::SIZE; ++i)
    lhs[i] -= rhs[i];
  return lhs;
}

template <ModifiableVector V>
V constexpr &operator*=(V &lhs, ComponentT<V> const k)
{
  for (size_t i = 0; i < V::SIZE; ++i)
    lhs[i] *= k;
  return lhs;
}

template <ModifiableVector V>
V constexpr &operator/=(V &lhs, ComponentT<V> const k)
{
  for (size_t i = 0; i < V::SIZE; ++i)
    lhs[i] /= k;
  return lhs;
}

template <Vector V>
ModifiableEquivalentT<V> constexpr operator-(V const &rhs)
{
  ModifiableEquivalentT<V> ret;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret[i] = -rhs[i];
  return ret;
}

template <Vector V>
ModifiableEquivalentT<V> constexpr operator*(V const &lhs, ComponentT<V> k)
{
  ModifiableEquivalentT<V> ret;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret[i] = lhs[i] * k;
  return ret;
}

template <Vector V>
ModifiableEquivalentT<V> constexpr operator*(ComponentT<V> k, V const &rhs)
{
  ModifiableEquivalentT<V> ret;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret[i] = rhs[i] * k;
  return ret;
}

template <Vector V>
ModifiableEquivalentT<V> constexpr operator/(
    V const &lhs, ComponentT<V> const k)
{
  ModifiableEquivalentT<V> ret;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret[i] = lhs[i] / k;
  return ret;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2>
ModifiableEquivalentT<V1> constexpr operator+(V1 const &lhs, V2 const &rhs)
{
  ModifiableEquivalentT<V1> ret;
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret[i] = lhs[i] + rhs[i];
  return ret;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2>
ModifiableEquivalentT<V1> constexpr operator-(V1 const &lhs, V2 const &rhs)
{
  ModifiableEquivalentT<V1> ret;
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret[i] = lhs[i] - rhs[i];
  return ret;
}

template <Vector V>
  requires(std::floating_point<ComponentT<V>>)
ComponentT<V> constexpr length(V const &v)
{
  ComponentT<V> ret = {};
  for (size_t i = 0; i < V::SIZE; ++i)
    ret += pow2(v[i]);
  return std::sqrt(ret);
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2> && std::floating_point<ComponentT<V1>>
ComponentT<V1> constexpr distance(V1 const &lhs, V2 const &rhs)
{
  ComponentT<V1> ret = {};
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret += pow2(lhs[i] - rhs[i]);
  return std::sqrt(ret);
}

template <Vector V>
  requires(std::floating_point<ComponentT<V>>)
V constexpr normalize(V const &v)
{
  auto const l = length(v);
  V ret;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret[i] = v[i] / l;
  return ret;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2>
ComponentT<V1> constexpr dot(V1 const &lhs, V2 const &rhs)
{
  ComponentT<V1> ret{ 0 };
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret += lhs[i] * rhs[i];
  return ret;
}

template <Vector V>
bool constexpr in_range(V const &v, V const &a, V const &b)
{
  bool ret = true;
  for (size_t i = 0; i < V::SIZE; ++i)
    ret = ret && in_range(v[i], a[i], b[i]);
  return ret;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2> && std::floating_point<ComponentT<V1>>
auto project(V1 const &a, V2 const &b)
{
  return b * (dot(a, b) / dot(b, b));
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2> && std::floating_point<ComponentT<V1>>
auto project_no_division(V1 const &a, V2 const &b)
{
  return b * (dot(a, b));
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2> && std::floating_point<ComponentT<V1>>
auto reject(V1 const &a, V2 const &b)
{
  return a - project(a, b);
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2> && std::floating_point<ComponentT<V1>>
auto reject_no_division(V1 const &a, V2 const &b)
{
  return a - project_no_division(a, b);
}
