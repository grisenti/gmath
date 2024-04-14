#pragma once

#include "gmath/base.hpp"
#include "gmath/numeric_utils.hpp"
#include "gmath/matrix/matrix_base.hpp"
#include <cmath>

namespace gmath
{

struct VectorTag
{
};

template <typename V>
concept Vector = Array<V> && InheritsFrom<V, VectorTag>;

/// Base class meant to remove duplicated code in the various Vector structs
template <size_t N, typename T>
struct VectorBase
{
  using ComponentType = T;
  static constexpr size_t SIZE = N;
};

template <typename V>
concept ModifiableVector = Vector<V> && ModifiableArray<V>;

template <typename V>
concept ConstVectorWrapper = Vector<V> && ConstArrayWrapper<V>
                             && SameTypeClass<V, ModifiableEquivalent<V>>;

/// Marker type for column vectors
struct ColumnVectorTag : ColumnMatrixTag, VectorTag
{
};

template <typename V>
concept ModifiableColumnVector
    = ModifiableColumnMatrix<V> && InheritsFrom<V, ColumnVectorTag>;

template <typename V>
concept ConstColumnVectorWrapper
    = ConstColumnMatrix<V> && InheritsFrom<V, ColumnVectorTag>;

/// Marker type for row vectors
struct RowVectorTag : RowMatrixTag, VectorTag
{
};

template <typename V>
concept ModifiableRowVector
    = ModifiableRowMatrix<V> && InheritsFrom<V, RowVectorTag>;

template <typename V>
concept ConstRowVectorWrapper
    = ConstRowMatrix<V> && InheritsFrom<V, RowVectorTag>;

template <typename V>
concept RowVector = ModifiableRowVector<V> || ConstRowVectorWrapper<V>;

template <typename V>
concept ColumnVector
    = ModifiableColumnVector<V> || ConstColumnVectorWrapper<V>;

template <typename V1, typename V2>
concept VectorCompatibleWeak
    = Vector<V1> && Vector<V2> && std::same_as<ComponentT<V1>, ComponentT<V2>>
      && (V1::SIZE == V2::SIZE);

template <typename V1, typename V2>
concept VectorCompatible
    = VectorCompatibleWeak<V1, V2> && SameTypeClass<V1, V2>
      && std::same_as<ModifiableEquivalentT<V1>, ModifiableEquivalentT<V2>>;

template <Vector V>
  requires std::equality_comparable<ComponentT<V>>
bool constexpr operator==(V const &lhs, V const &rhs)
{
  for (size_t i = 0; i < V::SIZE; ++i)
    if (!(lhs[i] == rhs[i]))
      return false;
  return true;
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

/// @returns The dot product of the two vectors. It does not require that the
/// two vectors have the same type class. It is used to implement dot product
/// between vectors and normals.
template <Vector V1, Vector V2>
  requires VectorCompatibleWeak<V1, V2>
ComponentT<V1> weak_dot(V1 const &lhs, V2 const &rhs)
{
  ComponentT<V1> ret{ 0 };
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret += lhs[i] * rhs[i];
  return ret;
}

template <Vector V>
ComponentT<V> constexpr dot(V const &lhs, V const &rhs)
{
  return weak_dot(lhs, rhs);
}

template <Vector V>
ComponentT<V> constexpr square_magnitude(V const &v)
{
  return dot(v, v);
}

template <Vector V>
  requires(std::floating_point<ComponentT<V>>)
ComponentT<V> constexpr magnitude(V const &v)
{
  return std::sqrt(square_magnitude(v));
}

template <Vector V>
  requires(std::floating_point<ComponentT<V>>)
ModifiableEquivalentT<V> constexpr normalize(V const &v)
{
  auto const l = magnitude(v);
  return v / l;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2>
ModifiableEquivalentT<V1> constexpr componentwise_mul(
    V1 const &lhs, V2 const &v2)
{
  ModifiableEquivalentT<V1> ret{};
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret[i] = lhs[i] * v2[i];
  return ret;
}

template <Vector V1, Vector V2>
  requires VectorCompatible<V1, V2>
ModifiableEquivalentT<V1> constexpr componentwise_div(
    V1 const &lhs, V2 const &v2)
{
  ModifiableEquivalentT<V1> ret{};
  for (size_t i = 0; i < V1::SIZE; ++i)
    ret[i] = lhs[i] / v2[i];
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

} // namespace gmath