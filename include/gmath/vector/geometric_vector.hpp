#pragma once

#include "vec_base.hpp"

namespace gmath
{

/// Marker type for geometric vectors, that represent a direction in space.
struct GeometricVectorTag : VectorTag
{
};

struct GeometricColumnVectorTag : GeometricVectorTag, ColumnVectorTag
{
};

struct GeometricRowVectorTag : GeometricVectorTag, RowVectorTag
{
};

/// Base class meant to remove duplicated code in the various Vector structs
template <size_t N, typename T>
struct GeometricColumnVectorBase
{
  using TypeClass = GeometricColumnVectorTag;
  using ComponentType = T;
  static constexpr size_t SIZE = N;
};

template <typename V>
concept GeometricVector = Vector<V> && InheritsFrom<V, GeometricVectorTag>;

template <GeometricVector V>
auto length(V const &v)
{
  return magnitude(v);
}

template <GeometricVector V1, GeometricVector V2>
  requires VectorCompatibleWeak<V1, V2>
auto dot(V1 const &a, V2 const &b)
{
  return weak_dot(a, b);
}

template <Vector V1, Vector V2, Vector V3>
  requires VectorCompatible<V1, V2> && VectorCompatible<V2, V3>
           && (V1::SIZE == 3)
ComponentT<V1> constexpr scalar_triple_product(
    V1 const &a, V2 const &b, V3 const &c)
{
  return dot(cross(a, b), c);
}

template <GeometricVector V1, GeometricVector V2>
  requires VectorCompatibleWeak<V1, V2> && std::floating_point<ComponentT<V1>>
auto project(V1 const &a, V2 const &b)
{
  return b * (dot(a, b) / dot(b, b));
}

template <GeometricVector V1, GeometricVector V2>
  requires VectorCompatibleWeak<V1, V2> && std::floating_point<ComponentT<V1>>
auto project_no_division(V1 const &a, V2 const &b)
{
  return b * (dot(a, b));
}

template <GeometricVector V1, GeometricVector V2>
  requires VectorCompatibleWeak<V1, V2> && std::floating_point<ComponentT<V1>>
auto reject(V1 const &a, V2 const &b)
{
  return a - project(a, b);
}

template <GeometricVector V1, GeometricVector V2>
  requires VectorCompatibleWeak<V1, V2> && std::floating_point<ComponentT<V1>>
auto reject_no_division(V1 const &a, V2 const &b)
{
  return a - project_no_division(a, b);
}

} // namespace gmath