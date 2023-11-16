#pragma once

#include "vec_base.hpp"

template <size_t N, typename T>
struct VecN
{
  using type_class = VectorTag;
  using component_type = T;
  static constexpr size_t size = N;

  T values[N];

  T operator[](size_t i) const
  {
    return values[i];
  }

  T &operator[](size_t i)
  {
    return values[i];
  }
};

template <size_t N>
using VecNf = VecN<N, float>;
template <size_t N>
using VecNi = VecN<N, int>;
template <size_t N>
using VecNu = VecN<N, unsigned>;
