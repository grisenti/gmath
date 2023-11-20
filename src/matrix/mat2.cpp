#include "mat2.hpp"

Real det(mat2f const &M)
{
  return M[0, 0] * M[1, 1] - M[0, 1] * M[1, 0];
}

mat2f inverse(mat2f const &M)
{
  auto const inv_det = 1.0f / det(M);
  // clang-format off
  return mat2f::from_rows({
      M[1, 1] * inv_det, -M[0, 1] * inv_det,
      -M[1, 0] * inv_det, M[0, 0] * inv_det
  });
  // clang-format on
}