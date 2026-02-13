#pragma once

#include <concepts>
#include <type_traits>

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

#define GMATH_CONST_ARRAY_MEMBER_ACCESS(array, ret_type) \
  ret_type const &operator[](size_t i) const \
  { \
  return array[i]; \
  }

#define GMATH_MODIFIABLE_ARRAY_MEMBER_ACCESS(array, ret_type) \
  GMATH_CONST_ARRAY_MEMBER_ACCESS(array, ret_type)\
  ret_type &operator[](size_t i) \
  { \
  return array[i];\
  }

#define GMATH_ARRAY_MEMBER_ACCESS_FOR_STANDARD_LAYOUT(T, array, ret_type) \
  ret_type const &operator[](size_t i) const \
  { \
    static_assert(::std::is_standard_layout_v<T>, #T " must be standard layout for operator[] to work"); \
    return array[i]; \
  } \
  ret_type &operator[](size_t i) \
  { \
    static_assert(::std::is_standard_layout_v<T>, #T " must be standard layout for operator[] to work"); \
    return array[i];\
  }