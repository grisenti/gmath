#include "line.hpp"

NormalizedLine NormalizedLine::from_line_unchecked(const Line &line)
{
  return NormalizedLine{ UnitVec<Vec3f>::create_unchecked(line.direction),
    line.moment };
}

NormalizedLine NormalizedLine::from_line(const Line &line)
{
  auto const l = length(line.direction);
  return NormalizedLine{ UnitVec<Vec3f>::create_unchecked(line.direction / l),
    line.moment / l };
}