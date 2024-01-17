#pragma once

#include <concepts>

namespace gmath
{

template <typename A>
concept Array = requires(A const &array) {
  typename A::ComponentType;
  A::SIZE;
  {
    array[0]
  } -> std::same_as<typename A::ComponentType const &>;
} && (A::SIZE * sizeof(typename A::ComponentType) == sizeof(A));

template <typename A>
concept ModifiableArray = Array<A> && requires(A arr) {
  {
    arr[0]
  } -> std::same_as<typename A::ComponentType &>;
};

template <Array A>
using ComponentT = typename A::ComponentType;

template <typename A>
concept ConstArrayWrapper
    = requires() { typename A::ModifiableEquivalent; }
      && Array<A> && Array<typename A::ModifiableEquivalent>
      && ModifiableArray<typename A::ModifiableEquivalent>
      && std::same_as<ComponentT<A>,
          ComponentT<typename A::ModifiableEquivalent>>
      && (A::SIZE == A::ModifiableEquivalent::SIZE);

template <Array M>
struct ModifiableEquivalent
{
};

template <ModifiableArray M>
struct ModifiableEquivalent<M>
{
  using Type = M;
};

template <ConstArrayWrapper M>
struct ModifiableEquivalent<M>
{
  using Type = typename M::ModifiableEquivalent;
};

template <typename T>
using ModifiableEquivalentT = ModifiableEquivalent<T>::Type;

template <Array A>
constexpr ComponentT<A> const *begin(A &array)
{
  return &array[0];
}

template <Array A>
constexpr ComponentT<A> const *end(A &array)
{
  return &array[0] + A::SIZE;
}

template <ModifiableArray A>
constexpr ComponentT<A> *begin(A &array)
{
  return &array[0];
}

template <ModifiableArray A>
constexpr ComponentT<A> *end(A &array)
{
  return &array[0] + A::SIZE;
}

} // namespace gmath