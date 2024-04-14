#include "gmath/matrix/mat2.hpp"

namespace gmath
{

Real det(Mat2f const &M)
{
  return M.entry(0, 0) * M.entry(1, 1) - M.entry(0, 1) * M.entry(1, 0);
}

Mat2f inverse(Mat2f const &M)
{
  auto const inv_det = 1.0f / det(M);
  // clang-format off
  return Mat2f::from_rows({
      M.entry(1, 1) * inv_det, -M.entry(0, 1) * inv_det,
      -M.entry(1, 0) * inv_det, M.entry(0, 0) * inv_det
  });
  // clang-format on
}

} // namespace gmath