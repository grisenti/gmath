#include "mat4.hpp"
#include "vector/vec3.hpp"
#include "vec.hpp"

// Both implementations are taken from "Foundations of Game Engine Development
// Volume 1 Mathematics" by Eric Lengyel.

Real det(mat4f const &M)
{
  auto const a = truncate(M.column(0));
  auto const b = truncate(M.column(1));
  auto const c = truncate(M.column(2));
  auto const d = truncate(M.column(3));
  auto const x = M[3, 0];
  auto const y = M[3, 1];
  auto const z = M[3, 2];
  auto const w = M[3, 3];

  auto const s = cross(a, b);
  auto const t = cross(c, d);
  auto const u = y * a - x * b;
  auto const v = w * c - z * d;

  return dot(s, v) + dot(t, u);
}

mat4f inverse(mat4f const &M)
{
  auto const a = truncate(M.column(0));
  auto const b = truncate(M.column(1));
  auto const c = truncate(M.column(2));
  auto const d = truncate(M.column(3));
  auto const x = M[3, 0];
  auto const y = M[3, 1];
  auto const z = M[3, 2];
  auto const w = M[3, 3];

  auto const s = cross(a, b);
  auto const t = cross(c, d);
  auto const u = y * a - x * b;
  auto const v = w * c - z * d;

  auto const inv_det = 1.0f / (dot(s, v) + dot(t, u));

  // clang-format off
    return mat4f::from_row_vecs({
      extend(cross(b, v) + y * t, -dot(b, t)) * inv_det,
      extend(cross(v, a) - x * t, dot(a, t)) * inv_det,
      extend(cross(d, u) + w * s, -dot(d, s)) * inv_det,
      extend(cross(u, c) - z * s, dot(c, s)) * inv_det
    });
  // clang-format on
}
