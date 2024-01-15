#pragma once

#include "vector/vec_base.hpp"
#include "vector/vec2.hpp"
#include "vector/vec3.hpp"
#include "vector/vec4.hpp"
#include "vector/vecn.hpp"
#include "vector/unit_vector.hpp"
#include "vector/octahedral_vector.hpp"

namespace gmath
{

template <Vector V>
  requires(V::SIZE > 1)
DefaultVectorOf<V::SIZE + 1, ComponentT<V>> extend(
    V const &v, ComponentT<V> value = {})
{
  DefaultVectorOf<V::SIZE + 1, ComponentT<V>> res;
  for (size_t i = 0; i < V::SIZE; ++i)
    res[i] = v[i];
  res[V::SIZE] = value;
  return res;
}

template <Vector V>
  requires(V::SIZE > 1)
DefaultVectorOf<V::SIZE - 1, ComponentT<V>> truncate(V const &v)
{
  DefaultVectorOf<V::SIZE - 1, ComponentT<V>> res;
  for (size_t i = 0; i < V::SIZE - 1; ++i)
    res[i] = v[i];
  return res;
}

using UVec2f = UnitVec<Vec2f>;
using UVec3f = UnitVec<Vec3f>;
using UVec4f = UnitVec<Vec4f>;

static UVec3f constexpr X3f = UVec3f::create_unchecked(1._r, 0._r, 0._r);
static UVec3f constexpr Y3f = UVec3f::create_unchecked(0._r, 1._r, 0._r);
static UVec3f constexpr Z3f = UVec3f::create_unchecked(0._r, 0._r, 1._r);

} // namespace gmath
