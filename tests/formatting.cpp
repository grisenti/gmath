#include "test.hpp"

#include "formatting.hpp"
#include "matrix/mat2.hpp"

TEST_CASE("format_vectors")
{
  REQUIRE(std::format("{}", Vec2{1, 2}) == "(1, 2)");
}

TEST_CASE("format_matrices")
{
  REQUIRE(std::format("{}", Mat2f::from_rows({1, 2, 3, 4})) == "[[1, 2][3, 4]]");
}

TEST_CASE("format_lines")
{
  REQUIRE(std::format("{}", Line{Vec3f{1, 2, 3}, Normal3f{3, 2, 1}}) == "{(1, 2, 3) | (3, 2, 1)}");
}

TEST_CASE("format_planes")
{
  REQUIRE(std::format("{}", Plane{Normal3f{3, 2, 1}, 1}) == "[(3, 2, 1) | 1]");
}
