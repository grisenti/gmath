#pragma once

#include <cassert>
#include <array>

#include "base.hpp"

struct Matrix1DTag
{
};

template <typename M>
concept ModifiableMatrix1D = requires(M const &cr_mat, M mat) {
  typename M::component_type;
  M::size;
  M{};
  {
    cr_mat[0]
  } -> std::same_as<typename M::component_type>;
  {
    mat[0]
  } -> std::same_as<typename M::component_type &>;
} && std::is_base_of_v<Matrix1DTag, typename M::type_class>;

template <typename M>
concept ConstMatrix1D = requires(M const &cr_mat, M mat) {
  typename M::component_type;
  typename M::modifiable_equivalent;
  M::size;
  {
    cr_mat[0]
  } -> std::same_as<typename M::component_type>;
} && ModifiableMatrix1D<typename M::modifiable_equivalent> && std::same_as<typename M::component_type, typename M::modifiable_equivalent::component_type> && (M::size == M::modifiable_equivalent::size) && std::is_base_of_v<Matrix1DTag, typename M::type_class>;

template <typename M>
concept Matrix1D = ConstMatrix1D<M> || ModifiableMatrix1D<M>;

struct RowMatrixTag : Matrix1DTag
{
};

struct ColumnMatrixTag : Matrix1DTag
{
};

template <typename M>
concept ModifiableRowMatrix
    = ModifiableMatrix1D<M>
      && std::is_base_of_v<RowMatrixTag, typename M::type_class>;

template <typename M>
concept ModifiableColumnMatrix
    = ModifiableMatrix1D<M>
      && std::is_base_of_v<ColumnMatrixTag, typename M::type_class>;

template <typename M>
concept ConstRowMatrix
    = ConstMatrix1D<M>
      && std::is_base_of_v<RowMatrixTag, typename M::type_class>;

template <typename M>
concept ConstColumnMatrix
    = ConstMatrix1D<M>
      && std::is_base_of_v<ColumnMatrixTag, typename M::type_class>;

template <typename M>
concept RowMatrix
    = Matrix1D<M> && std::is_base_of_v<RowMatrixTag, typename M::type_class>;

template <typename M>
concept ColumnMatrix
    = Matrix1D<M>
      && std::is_base_of_v<ColumnMatrixTag, typename M::type_class>;

template <Matrix1D M>
struct ModifiableEquivalent
{
};

template <ConstMatrix1D M>
struct ModifiableEquivalent<M>
{
  using type = typename M::modifiable_equivalent;
};

template <ModifiableMatrix1D M>
struct ModifiableEquivalent<M>
{
  using type = M;
};

template <typename T>
using ModifiableEquivalentT = ModifiableEquivalent<T>::type;

/// The type of V's components
template <Matrix1D M>
using ComponentT = typename M::component_type;