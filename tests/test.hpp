#include <catch2/catch_all.hpp>
#include <iostream>

#include "gmath/vec.hpp"
#include "gmath/mat.hpp"
#include "gmath/formatting.hpp"

template <Vector V>
std::ostream &operator<<(std::ostream &out, V const &v)
{
  out << std::format("{}", v);
  return out;
}

template <typename T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &out, Matrix<R, C, T> const &mat)
{
  out << std::format("{}", mat);
  return out;
}
