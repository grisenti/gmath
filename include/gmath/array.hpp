#pragma once

#include <concepts>

template <typename A>
concept Array = requires(A const &array) {
  typename A::ComponentType;
  A::SIZE;
  {
    array[0]
  } -> std::same_as<typename A::ComponentType>;
};

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