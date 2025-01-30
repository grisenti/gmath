#include "gmath/geometry/plane.hpp"

#include <limits>

namespace gmath
{

Plane Plane::from_points(
    const Point3f &p1, const Point3f &p2, const Point3f &p3)
{
  auto const n
      = Normal3f::cross(as_vec3(p2) - as_vec3(p1), as_vec3(p3) - as_vec3(p1));
  return { n, -dot(n, as_vec3(p1)) };
}

std::optional<Point3f> intersection_point(
    Plane const &p1, Plane const &p2, Plane const &p3)
{
  auto const &n1 = p1.normal;
  auto const &n2 = p2.normal;
  auto const &n3 = p3.normal;

  auto const n1xn2 = cross(n1, n2);
  auto const det = dot(n1xn2, n3);
  if (std::abs(det) > std::numeric_limits<Real>::epsilon())
  {
    return as_point3(
        (cross(n3, n2) * p1.d + cross(n1, n3) * p2.d - n1xn2 * p3.d) / det);
  }
  return std::nullopt;
}

NormalizedPlane NormalizedPlane::from_plane_unchecked(Plane const &plane)
{
  return { UnitVec<Normal3f>::create_unchecked(plane.normal), plane.d };
}

NormalizedPlane NormalizedPlane::from_plane(const Plane &plane)
{
  auto l = magnitude(plane.normal);
  return { UnitVec<Normal3f>::create_unchecked(plane.normal / l),
    plane.d / l };
}

Real signed_distance(NormalizedPlane const &plane, Point3f const &point)
{
  static_assert(ConstRowVectorWrapper<UnitVec<Normal3f>>);
  return dot(as_vec3(point), plane.normal) + plane.d;
}

} // namespace gmath