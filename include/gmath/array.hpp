#pragma once

#include <concepts>
#include <type_traits>

namespace gmath
{

template <typename A>
concept Array = requires(A const &array) {
  typename A::ComponentType;
  { A::SIZE } -> std::same_as<size_t const &>;
  { array[0] } -> std::same_as<typename A::ComponentType const &>;
};

template <typename A>
concept ModifiableArray = Array<A> && requires(A arr) {
  { arr[0] } -> std::same_as<typename A::ComponentType &>;
} && std::is_default_constructible_v<A>;

template <Array A>
using ComponentT = typename A::ComponentType;

template <typename A>
concept ConstArray
    = requires() { typename A::ModifiableEquivalent; }
      && Array<A> && ModifiableArray<typename A::ModifiableEquivalent>
      && std::same_as<ComponentT<A>,
          ComponentT<typename A::ModifiableEquivalent>>
      && (A::SIZE == A::ModifiableEquivalent::SIZE);

template <Array A>
struct ModifiableEquivalent
{
};

template <ModifiableArray A>
struct ModifiableEquivalent<A>
{
  using Type = A;
};

template <ConstArray A>
struct ModifiableEquivalent<A>
{
  using Type = typename A::ModifiableEquivalent;
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

template <typename T>
concept TypeClassed = requires(T t) { typename T::TypeClass; };

template <typename T, typename U>
concept SameTypeClass
    = TypeClassed<T> && TypeClassed<U>
      && std::same_as<typename T::TypeClass, typename U::TypeClass>;

template <TypeClassed T, typename C>
struct IsOfTypeClassT
{
  static constexpr bool VALUE = std::is_base_of_v<C, typename T::TypeClass>;
};

template <typename T, typename C>
concept IsOfTypeClass = IsOfTypeClassT<T, C>::VALUE;

} // namespace gmath

#define GMATH_CONST_ARRAY_MEMBER_ACCESS(array, ret_type)                      \
  ret_type const &operator[](size_t i) const                                  \
  {                                                                           \
    return array[i];                                                          \
  }

#define GMATH_MODIFIABLE_ARRAY_MEMBER_ACCESS(array, ret_type)                 \
  GMATH_CONST_ARRAY_MEMBER_ACCESS(array, ret_type)                            \
  ret_type &operator[](size_t i)                                              \
  {                                                                           \
    return array[i];                                                          \
  }

#define GMATH_ARRAY_MEMBER_ACCESS_FOR_STANDARD_LAYOUT(T, array, ret_type)     \
  ret_type const &operator[](size_t i) const                                  \
  {                                                                           \
    static_assert(::std::is_standard_layout_v<T>,                             \
        #T " must be standard layout for operator[] to work");                \
    return array[i];                                                          \
  }                                                                           \
  ret_type &operator[](size_t i)                                              \
  {                                                                           \
    static_assert(::std::is_standard_layout_v<T>,                             \
        #T " must be standard layout for operator[] to work");                \
    return array[i];                                                          \
  }
