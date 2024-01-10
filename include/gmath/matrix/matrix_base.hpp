#pragma once

#include <cassert>
#include <array>

#include "gmath/base.hpp"
#include "gmath/array.hpp"

namespace gmath
{

struct Matrix1DTag
{
};

template <typename T>
concept TypeClassed = requires(T t) { typename T::TypeClass; };

template <typename T, typename U>
concept SameTypeClass
    = std::same_as<typename T::TypeClass, typename U::TypeClass>;

template <TypeClassed T, typename C>
struct InheritsFromT
{
  static constexpr bool VALUE = std::is_base_of_v<C, typename T::TypeClass>;
};

template <typename T, typename C>
concept InheritsFrom = InheritsFromT<T, C>::VALUE;

template <typename M>
concept ModifiableMatrix1D
    = ModifiableArray<M> && InheritsFrom<M, Matrix1DTag>;

template <typename M>
concept ConstMatrix1DWrapper
    = ConstArrayWrapper<M> && InheritsFrom<M, Matrix1DTag>
      && SameTypeClass<M, ModifiableEquivalentT<M>>;

template <typename M>
concept Matrix1D = ConstMatrix1DWrapper<M> || ModifiableMatrix1D<M>;

struct RowMatrixTag : Matrix1DTag
{
};

struct ColumnMatrixTag : Matrix1DTag
{
};

template <typename M>
concept ModifiableRowMatrix
    = ModifiableMatrix1D<M> && InheritsFrom<M, RowMatrixTag>;

template <typename M>
concept ModifiableColumnMatrix
    = ModifiableMatrix1D<M> && InheritsFrom<M, ColumnMatrixTag>;

template <typename M>
concept ConstRowMatrix
    = ConstMatrix1DWrapper<M> && InheritsFrom<M, RowMatrixTag>;

template <typename M>
concept ConstColumnMatrix
    = ConstMatrix1DWrapper<M> && InheritsFrom<M, ColumnMatrixTag>;

template <typename M>
concept RowMatrix = Matrix1D<M> && InheritsFrom<M, RowMatrixTag>;

template <typename M>
concept ColumnMatrix = Matrix1D<M> && InheritsFrom<M, ColumnMatrixTag>;

} // namespace gmath