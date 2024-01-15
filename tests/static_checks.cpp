#include "test.hpp"

#include "gmath/vec.hpp"

static_assert(Vec2f::SIZE == 2);
static_assert(ModifiableColumnMatrix<Vec2f>);
static_assert(GeometricVector<Vec2f>);

static_assert(Vec3f::SIZE == 3);
static_assert(ModifiableColumnMatrix<Vec3f>);
static_assert(GeometricVector<Vec3f>);

static_assert(Vec4f::SIZE == 4);
static_assert(ModifiableColumnMatrix<Vec4f>);
static_assert(Vector<Vec4f>);

static_assert(VecN<27, int>::SIZE == 27);
static_assert(ModifiableColumnMatrix<VecN<17, Real>>);
static_assert(Vector<VecN<17, double>>);

static_assert(UVec3f::SIZE == 3);
static_assert(ConstColumnVectorWrapper<UVec3f>);
static_assert(GeometricVector<UVec3f>);
