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

template <typename M>
concept ModifiableMatrix1D
    = ModifiableArray<M> && IsOfTypeClass<M, Matrix1DTag>;

template <typename M>
concept ConstMatrix1DWrapper = ConstArray<M> && IsOfTypeClass<M, Matrix1DTag>
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
    = ModifiableMatrix1D<M> && IsOfTypeClass<M, RowMatrixTag>;

template <typename M>
concept ModifiableColumnMatrix
    = ModifiableMatrix1D<M> && IsOfTypeClass<M, ColumnMatrixTag>;

template <typename M>
concept ConstRowMatrix
    = ConstMatrix1DWrapper<M> && IsOfTypeClass<M, RowMatrixTag>;

template <typename M>
concept ConstColumnMatrix
    = ConstMatrix1DWrapper<M> && IsOfTypeClass<M, ColumnMatrixTag>;

template <typename M>
concept RowMatrix = Matrix1D<M> && IsOfTypeClass<M, RowMatrixTag>;

template <typename M>
concept ColumnMatrix = Matrix1D<M> && IsOfTypeClass<M, ColumnMatrixTag>;

} // namespace gmath