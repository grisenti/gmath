#include <catch2/catch_all.hpp>
#include <iostream>

#include "vec.hpp"
#include "mat.hpp"

template <Vec V>
std::ostream &operator<<(std::ostream &out, V const &v)
{
  out << "(";
  for (size_t i = 0; i < V::size; ++i)
    out << v[i] << ", ";
  out << ")";
  return out;
}

template <typename T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &out, Matrix<R, C, T> const &mat)
{
  for (size_t i = 0; i < R; ++i)
  {
    for (size_t j = 0; j < C; ++j)
    {
      out << mat[i, j] << " ";
    }
    out << "\n";
  }
  return out;
}
