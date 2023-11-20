#pragma once

#include <cstdint>

#include "base.hpp"
#include "vec3.hpp"
#include "unit_vector.hpp"

/// More space efficient representation of a 3D unit vector. Implementation
/// taken from Physically Based Rendering 4th ed.
class OctahedralVector
{
public:
  OctahedralVector(UnitVec<Vec3f> const &v);

  UnitVec<Vec3f> into_unit_vec3() const;

private:
  std::uint16_t _x;
  std::uint16_t _y;
};