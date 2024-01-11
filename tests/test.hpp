#include <iostream>
#include <catch2/catch_all.hpp>

#include "gmath/vec.hpp"
#include "gmath/mat.hpp"
#include "gmath/formatting.hpp"

namespace gmath
{

template <Matrix1D V>
std::ostream &operator<<(std::ostream &out, V const &v)
{
  return out << std::format("{}", v);
}

template <typename T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &out, Matrix<R, C, T> const &mat)
{
  return out << std::format("{}", mat);
}

inline std::ostream &operator<<(std::ostream &out, Line const &l)
{
  return out << std::format("{}", l);
}

inline std::ostream &operator<<(std::ostream &out, Plane const &p)
{
  return out << std::format("{}", p);
}

}

using namespace gmath;