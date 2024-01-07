#include "mat3.hpp"
#include "vector/vec3.hpp"

Real det(mat3f const &M)
{
  return M[0, 0] * M[1, 1] * M[2, 2] + M[0, 1] * M[1, 2] * M[2, 0]
         + M[0, 2] * M[1, 0] * M[2, 1] - M[0, 0] * M[1, 2] * M[2, 1]
         - M[0, 1] * M[1, 0] * M[2, 2] - M[0, 2] * M[1, 1] * M[2, 0];
}

mat3f adj(mat3f const &M)
{
  auto const a = M.column(0);
  auto const b = M.column(1);
  auto const c = M.column(2);

  // clang-format off
  return mat3f::from_row_vecs({
      cross(b, c),
      cross(c, a),
      cross(a, b),
  });
  // clang-format on
}

mat3f inverse(mat3f const &M)
{
  auto const a = M.column(0);
  auto const b = M.column(1);
  auto const c = M.column(2);

  auto const r0 = cross(b, c);
  auto const r1 = cross(c, a);
  auto const r2 = cross(a, b);
  auto const inv_det = 1._r / dot(r2, c);
  // clang-format off
  return mat3f::from_row_vecs({
    r0 * inv_det,
    r1 * inv_det,
    r2 * inv_det
  });
  // clang-format on
}