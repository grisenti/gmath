#pragma once

#include <concepts>
#include <functional>
#include <algorithm>

#include "base.hpp"
#include "array.hpp"

namespace gmath
{

template <Array A, typename Comp = std::less<ComponentT<A>>>
  requires std::strict_weak_order<Comp, ComponentT<A>, ComponentT<A>>
constexpr size_t max_component_index(A const &array, Comp comp = {})
{
  // the value can never be negative, so this cast is safe.
  return static_cast<size_t>(std::distance(
      begin(array), std::max_element(begin(array), end(array), comp)));
}

template <Array A, typename Comp = std::less<ComponentT<A>>>
  requires std::strict_weak_order<Comp, ComponentT<A>, ComponentT<A>>
constexpr size_t min_component_index(A const &array, Comp comp = {})
{
  // the value can never be negative, so this cast is safe.
  return static_cast<size_t>(std::distance(
      begin(array), std::min_element(begin(array), end(array), comp)));
}

template <Array A>
ModifiableEquivalentT<A> permute(
    A const &original, std::array<size_t, A::SIZE> permutation_order)
{
  auto result = ModifiableEquivalentT<A>{};
  for (size_t dest = 0; auto const src : permutation_order)
  {
    result[dest] = original[src];
    ++dest;
  }
  return result;
}

template <Array A>
ModifiableEquivalentT<A> abs(A const &array)
{
  using std::abs;

  auto result = ModifiableEquivalentT<A>{};
  for (size_t i = 0; i < A::SIZE; ++i)
  {
    result[i] = abs(array[i]);
  }
  return result;
}

}