#pragma once

#include "normal3.hpp"
#include "vector/unit_vector.hpp"

struct Line
{
  Vec3f direction;
  Normal3f moment;
};

struct NormalizedLine
{
  /// Creates a NormalizedLine from a Line without checking that the direction
  /// has unitary length.
  static NormalizedLine from_line_unchecked(Line const &line);

  /// Creates a NormalizedLine from a Line dividing both the direction and
  /// moment by the length of the direction.
  static NormalizedLine from_line(Line const &line);

  UnitVec<Vec3f> direction;
  Normal3f moment;
};