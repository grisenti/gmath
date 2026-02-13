#pragma once

#include "geometric_vector.hpp"
#include "gmath/debug.hpp"

namespace gmath
{

template <typename T>
struct Vec2 : GeometricColumnVectorBase<2, T>
{
  T x;
  T y;

  constexpr Vec2() = default;

  constexpr Vec2(T x, T y) : x(x), y(y)
  {
    GMATH_DEBUG_ASSERT(!contains_nan(*this));
  }

  GMATH_ARRAY_MEMBER_ACCESS_FOR_STANDARD_LAYOUT(Vec2<T>, (&x), T)
};

template <Array A>
  requires(A::SIZE >= 2)
Vec2<ComponentT<A>> constexpr as_vec2(A const &a)
{
  return { a[0], a[1] };
}

using Vec2f = Vec2<Real>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;

} // namespace gmath
