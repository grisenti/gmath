#pragma once

#include <optional>

#include "gmath/geometry/normal3.hpp"
#include "gmath/vector/unit_vector.hpp"
#include "gmath/geometry/point.hpp"

struct Plane
{
  Normal3f normal;
  Real d;

  bool operator==(Plane const &rhs) const = default;
};

/// returns the intersection point between the three planes (if there is one).
std::optional<Point3f> intersection_point(
    Plane const &p1, Plane const &p2, Plane const &p3);

struct NormalizedPlane
{
  /// Creates a NormalizedPlane from a Plane without checking that the normal
  /// has unitary length.
  static NormalizedPlane from_plane_unchecked(Plane const &plane);

  /// Creates a NormalizedPlane from a Plane dividing both the normal and d by
  /// the length of the normal.
  static NormalizedPlane from_plane(Plane const &plane);

  // NOLINT: normalized planes are planes
  operator Plane() const
  {
    return { normal, d };
  }

  bool operator==(NormalizedPlane const &rhs) const = default;

  UnitVec<Normal3f> normal = UnitVec<Normal3f>::create_unchecked(0, 0, 1);
  Real d = 0;
};

Real signed_distance(NormalizedPlane const &plane, Point3f const &point);