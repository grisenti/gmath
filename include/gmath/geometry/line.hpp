#pragma once

#include "gmath/geometry/normal3.hpp"
#include "gmath/vector/unit_vector.hpp"
#include "gmath/vector/vec3.hpp"

namespace gmath
{

struct Line
{
  bool operator==(Line const &rhs) const = default;

  Vec3f direction;
  Normal3f moment;
};

struct NormalizedLine
{
  /// Creates a NormalizedLine from a Line without checking that the direction
  /// has unitary magnitude.
  static NormalizedLine from_line_unchecked(Line const &line);

  /// Creates a NormalizedLine from a Line dividing both the direction and
  /// moment by the magnitude of the direction.
  static NormalizedLine from_line(Line const &line);

  // NOLINT: normalized lines are lines
  operator Line() const
  {
    return { direction, moment };
  }

  bool operator==(NormalizedLine const &rhs) const = default;

  UnitVec<Vec3f> direction;
  Normal3f moment;
};

} // namespace gmath
