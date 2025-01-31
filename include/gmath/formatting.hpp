#pragma once

#ifdef __cpp_lib_format

#include <format>
#include <algorithm>

#include "gmath/vec.hpp"
#include "gmath/geometry.hpp"
#include "gmath/mat.hpp"
#include "gmath/units.hpp"

template <gmath::Matrix1D T>
struct std::formatter<T>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(T const &v, std::format_context &ctx) const
  {
    if constexpr (T::SIZE > 0)
    {
      auto result = std::string{ "(" };
      std::format_to(std::back_inserter(result), "{}", v[0]);
      if constexpr (T::SIZE > 1)
      {
        for (size_t i = 1; i < T::SIZE; ++i)
          std::format_to(std::back_inserter(result), ", {}", v[i]);
      }
      result += ")";
      return std::ranges::copy(result, ctx.out()).out;
    }
    return ctx.out();
  }
};

template <typename T, size_t R, size_t C>
struct std::formatter<gmath::Matrix<R, C, T>>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(gmath::Matrix<R, C, T> const &M, std::format_context &ctx) const
  {
    auto res = std::string{ "[" };
    for (size_t i = 0; i < R; ++i)
    {
      res += "[";
      for (size_t j = 0; j < C - 1; ++j)
      {
        std::format_to(std::back_inserter(res), "{}, ", M.entry(i, j));
      }
      std::format_to(std::back_inserter(res), "{}", M.entry(i, C - 1));
      res += "]";
    }
    res += "]";
    return std::ranges::copy(res, ctx.out()).out;
  }
};

template <>
struct std::formatter<gmath::Line>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(gmath::Line const &l, std::format_context &ctx) const
  {
    return std::format_to(ctx.out(), "{{{} | {}}}", l.direction, l.moment);
  }
};

template <>
struct std::formatter<gmath::Plane>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(gmath::Plane const &plane, std::format_context &ctx) const
  {
    return std::format_to(ctx.out(), "[{} | {}]", plane.normal, plane.d);
  }
};

#endif // __cpp_lib_format
