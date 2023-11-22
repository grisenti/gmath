#pragma once

#include <cassert>
#include <array>

#include "base.hpp"

struct Matrix1DTag
{
};

template <typename M>
concept ModifiableMatrix1D = requires(M const &cr_mat, M mat) {
  typename M::ComponentType;
  M::SIZE;
  M{};
  {
    cr_mat[0]
  } -> std::same_as<typename M::ComponentType>;
  {
    mat[0]
  } -> std::same_as<typename M::ComponentType &>;
} && std::is_base_of_v<Matrix1DTag, typename M::TypeClass>;

template <typename M>
concept ConstMatrix1D = requires(M const &cr_mat, M mat) {
  typename M::ComponentType;
  typename M::ModifiableEquivalent;
  M::SIZE;
  {
    cr_mat[0]
  } -> std::same_as<typename M::ComponentType>;
} && ModifiableMatrix1D<typename M::ModifiableEquivalent> && std::same_as<typename M::ComponentType, typename M::ModifiableEquivalent::ComponentType> && (M::SIZE == M::ModifiableEquivalent::SIZE) && std::is_base_of_v<Matrix1DTag, typename M::TypeClass>;

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
      && std::is_base_of_v<RowMatrixTag, typename M::TypeClass>;

template <typename M>
concept ModifiableColumnMatrix
    = ModifiableMatrix1D<M>
      && std::is_base_of_v<ColumnMatrixTag, typename M::TypeClass>;

template <typename M>
concept ConstRowMatrix
    = ConstMatrix1D<M>
      && std::is_base_of_v<RowMatrixTag, typename M::TypeClass>;

template <typename M>
concept ConstColumnMatrix
    = ConstMatrix1D<M>
      && std::is_base_of_v<ColumnMatrixTag, typename M::TypeClass>;

template <typename M>
concept RowMatrix
    = Matrix1D<M> && std::is_base_of_v<RowMatrixTag, typename M::TypeClass>;

template <typename M>
concept ColumnMatrix
    = Matrix1D<M> && std::is_base_of_v<ColumnMatrixTag, typename M::TypeClass>;

template <Matrix1D M>
struct ModifiableEquivalent
{
};

template <ConstMatrix1D M>
struct ModifiableEquivalent<M>
{
  using Type = typename M::ModifiableEquivalent;
};

template <ModifiableMatrix1D M>
struct ModifiableEquivalent<M>
{
  using Type = M;
};

template <typename T>
using ModifiableEquivalentT = ModifiableEquivalent<T>::Type;

/// The type of V's components
template <Matrix1D M>
using ComponentT = typename M::ComponentType;