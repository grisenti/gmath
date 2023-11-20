#include "octahedral_vector.hpp"

namespace
{

constexpr Real u16_max = 65535._r;

std::uint16_t encode(Real x)
{
  return std::round(clamp((x + 1) / 2, 0._r, 1._r) * u16_max);
}

float sign(Real x)
{
  return std::copysign(1.f, x);
}

}

OctahedralVector::OctahedralVector(UnitVec<Vec3f> const &uv)
{
  auto v = uv.unwrap();
  v /= std::abs(v.x) + std::abs(v.y) + std::abs(v.z);
  if (v.z >= 0)
  {
    _x = encode(v.x);
    _y = encode(v.y);
  }
  else
  {
    // for v.x > 0 and v.y > 0, _x = 1 - v.y and _y = 1 - v.x
    // all other cases are mapped to the previous one and
    // the sign is adjusted at the end with sign(.)
    _x = encode((1 - std::abs(v.y)) * sign(v.x));
    _y = encode((1 - std::abs(v.x)) * sign(v.y));
  }
}

UnitVec<Vec3f> OctahedralVector::into_unit_vec3() const
{
  auto x = -1 + 2 * (_x / u16_max);
  auto y = -1 + 2 * (_y / u16_max);
  auto const z = 1 - (std::abs(x) + std::abs(y));
  if (z < 0)
  {
    auto const xt = x;
    x = (1 - std::abs(y)) * sign(xt);
    y = (1 - std::abs(xt)) * sign(xt);
  }
  return UnitVec<Vec3f>::normalize(x, y, z);
}