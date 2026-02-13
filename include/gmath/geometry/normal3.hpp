#pragma once

#include "gmath/vector/vec3.hpp"
#include "gmath/vector/unit_vector.hpp"

namespace gmath
{

struct NormalTag : GeometricRowVectorTag
{
};

template <typename N>
concept Normal = RowVector<N> && InheritsFrom<N, NormalTag>;

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
    requires VectorCompatibleWeak<V1, V2> && std::same_as<ComponentT<V1>, T>
             && (V1::SIZE == 3)
  static Normal3 cross(V1 const &lhs, V2 const &rhs)
  {
    return Normal3{ ::gmath::cross(lhs, rhs) };
  }

  Normal3() = default;

  explicit Normal3(Vec3<T> const &v) : x(v.x), y(v.y), z(v.z)
  {
  }

  Normal3(T x, T y, T z) : x(x), y(y), z(z)
  {
  }

  GMATH_ARRAY_MEMBER_ACCESS_FOR_STANDARD_LAYOUT(Normal3<T>, (&x), T)
};

using Normal3f = Normal3<Real>;
using UNormal3f = UnitVec<Normal3f>;

} // namespace gmath
