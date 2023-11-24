#pragma once

#include "normal3.hpp"
#include "vector/unit_vector.hpp"
#include "point.hpp"

struct Plane
{
  Normal3f normal;
  Real d;
};

struct NormalizedPlane
{
  /// Creates a NormalizedPlane from a Plane without checking that the normal
  /// has unitary length.
  static NormalizedPlane from_plane_unchecked(Plane const &plane);

  /// Creates a NormalizedPlane from a Plane dividing both the normal and d by
  /// the length of the normal.
  static NormalizedPlane from_plane(Plane const &plane);

  UnitVec<Normal3f> normal;
  Real d;
};

Real signed_distance(NormalizedPlane const &plane, Point3f const &point);