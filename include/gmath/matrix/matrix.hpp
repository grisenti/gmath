#pragma once

#include "gmath/matrix/matrix_base.hpp"
#include "gmath/vector/vecn.hpp"
#include "gmath/debug.hpp"

namespace gmath
{

/// column major matrix
template <size_t R, size_t C, typename T>
struct Matrix
{
  using RowVec = DefaultVectorOf<C, T>;
  using ColumnVec = DefaultVectorOf<R, T>;

  T values[R * C];

  static constexpr Matrix diagonal(T const diagonal)
  {
    auto res = Matrix{};
    for (size_t j = 0; j < C; ++j)
      for (size_t i = 0; i < R; ++i)
        res[i, j] = i == j ? diagonal : 0;
    return res;
  }

  static constexpr Matrix diagonal(DefaultVectorOf<std::min(R, C), T> diagonal)
  {
    auto res = Matrix{};
    for (size_t j = 0; j < C; ++j)
      for (size_t i = 0; i < R; ++i)
        res[i, j] = i == j ? diagonal[i] : 0;
    return res;
  }

  static constexpr Matrix from_rows(std::array<T, C * R> const &rows)
  {
    auto res = Matrix{};
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        res[i, j] = rows[i * C + j];
    return res;
  }

  static constexpr Matrix from_row_vecs(std::array<RowVec, R> const &rows)
  {
    auto res = Matrix{};
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        res[i, j] = rows[i][j];
    return res;
  }

  static constexpr Matrix from_columns(std::array<T, C * R> const &cols)
  {
    auto res = Matrix{};
    for (size_t i = 0; i < C * R; ++i)
      res.values[i] = cols[i];
    return res;
  }

  static constexpr Matrix from_column_vecs(
      std::array<ColumnVec, C> const &cols)
  {
    auto res = Matrix{};
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j)
        res[i, j] = cols[j][i];
    return res;
  }

  Matrix constexpr &transpose()
    requires(R == C)
  {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = i; j < R; ++j)
        std::swap(values[j + i * R], values[i + j * R]);
    return *this;
  }

  T constexpr &operator[](size_t i, size_t j)
  {
    GMATH_DEBUG_ASSERT(i < R && j < C);
    return values[i + j * R];
  }

  T constexpr operator[](size_t i, size_t j) const
  {
    GMATH_DEBUG_ASSERT(i < R && j < C);
    return values[i + j * R];
  }

  RowVec constexpr row(size_t i) const
  {
    auto res = RowVec{};
    for (size_t j = 0; j < C; ++j)
      res[j] = values[i + j * R];
    return res;
  }

  ColumnVec constexpr column(size_t j) const
  {
    auto res = ColumnVec{};
    for (size_t i = 0; i < R; ++i)
      res[i] = values[i + j * R];
    return res;
  }
};

template <size_t R1, size_t C1, size_t C2, Numeric T>
Matrix<R1, C2, T> constexpr operator*(
    Matrix<R1, C1, T> const &lhs, Matrix<C1, C2, T> const &rhs)
{
  auto res = Matrix<R1, C2, T>::diagonal(0);
  for (size_t i = 0; i < R1; ++i)
    for (size_t j = 0; j < C2; ++j)
      for (size_t k = 0; k < C1; ++k)
      {
        res[i, j] += lhs[i, k] * rhs[k, j];
      }
  return res;
}

template <size_t R, size_t C, Numeric T, ColumnMatrix V>
  requires(V::SIZE == R) && std::same_as<ComponentT<V>, T>
ModifiableEquivalentT<V> constexpr operator*(
    Matrix<R, C, T> const &lhs, V const &rhs)
{
  auto res = ModifiableEquivalentT<V>{};
  for (size_t j = 0; j < C; ++j)
    for (size_t i = 0; i < R; ++i)
      res[i] += lhs[i, j] * rhs[j];
  return res;
}

template <size_t R, size_t C, Numeric T, RowMatrix V>
  requires(V::SIZE == C) && std::same_as<ComponentT<V>, T>
ModifiableEquivalentT<V> constexpr operator*(
    V const &lhs, Matrix<R, C, T> const &rhs)
{
  auto res = ModifiableEquivalentT<V>{};
  for (size_t j = 0; j < C; ++j)
    for (size_t i = 0; i < R; ++i)
      res[j] += lhs[j] * rhs[i, j];
  return res;
}

template <size_t R, size_t C, typename T>
Matrix<C, R, T> constexpr transpose(Matrix<R, C, T> const &mat)
{
  auto res = Matrix<C, R, T>::diagonal(0);
  for (size_t j = 0; j < C; ++j)
    for (size_t i = 0; i < R; ++i)
      res[j, i] = mat[i, j];
  return res;
}

} // namespace gmath