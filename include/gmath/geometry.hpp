#pragma once

#include "base.hpp"
#include "geometry/point.hpp"
#include "geometry/line.hpp"
#include "geometry/plane.hpp"

namespace gmath
{

inline Line join(Point3f const &p1, Point3f const &p2)
{
  return { p2 - p1, Normal3f::cross(as_vec3(p1), as_vec3(p2)) };
}

inline Plane join(Line const &L, Point3f const &p)
{
  return {
    Normal3f{L.direction.y * p.z - L.direction.z * p.y + L.moment.x,
             L.direction.z * p.x - L.direction.x * p.z + L.moment.y,
             L.direction.x * p.y - L.direction.y * p.x + L.moment.z},
    -dot(L.moment, as_vec3(p))
  };
}

inline Plane join(Point3f const &p, Line const &L)
{
  return join(L, p);
}

inline Line meet(Plane const &f, Plane const &g)
{
  return {
    Vec3f{f.normal.y * g.normal.z - f.normal.z * g.normal.y,
          f.normal.z * g.normal.x - f.normal.x * g.normal.z,
          f.normal.x * g.normal.y - f.normal.y * g.normal.x},
    Normal3f{ g.normal.x * f.d - f.normal.x * g.d,
          g.normal.y * f.d - f.normal.y * g.d,
          g.normal.z * f.d - f.normal.z * g.d              }
  };
}

inline HPoint3f meet(Line const &L, Plane const &f)
{
  auto const [fx, fy, fz] = f.normal;
  auto const [mx, my, mz] = L.moment;
  auto const [dx, dy, dz] = L.direction;
  // clang-format off
  return {
    my * fz - mz * fy + dx * f.d,
    mz * fx - mx * fz + dy * f.d,
    mx * fy - my * fx + dz * f.d,
    - dx * fx - dy * fy - dz * fz
  };
  // clang-format on
}

inline HPoint3f meet(Plane const &f, Line const &L)
{
  return meet(L, f);
}

} // namespace gmath
