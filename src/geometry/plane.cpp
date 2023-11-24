#include "plane.hpp"

NormalizedPlane NormalizedPlane::from_plane_unchecked(Plane const &plane)
{
  return { UnitVec<Normal3f>::create_unchecked(plane.normal), plane.d };
}

NormalizedPlane NormalizedPlane::from_plane(const Plane &plane)
{
  auto l = length(plane.normal);
  return { UnitVec<Normal3f>::create_unchecked(plane.normal / l),
    plane.d / l };
}

Real distance(NormalizedPlane const &plane, Point3f const &point)
{
  return dot(as_vec3(point), plane.normal) + plane.d;
}