#include "mat3.hpp"
#include "vector/vec3.hpp"

float det(mat3f const &M)
{
  return M[0, 0] * M[1, 1] * M[2, 2] + M[0, 1] * M[1, 2] * M[2, 0]
         + M[0, 2] * M[1, 0] * M[2, 1] - M[0, 0] * M[1, 2] * M[2, 1]
         - M[0, 1] * M[1, 0] * M[2, 2] - M[0, 2] * M[1, 1] * M[2, 0];
}

mat3f inverse(mat3f const &M)
{
  auto const a = M.column(0);
  auto const b = M.column(1);
  auto const c = M.column(2);
  auto const d = det(M);
  // clang-format off
  return mat3f::from_row_vecs({
      cross(b, c) / d,
      cross(c, a) / d,
      cross(a, b) / d,
  });
  // clang-format on
}