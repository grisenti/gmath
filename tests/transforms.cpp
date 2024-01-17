#include "test.hpp"

#include "gmath/transform/transform2D.hpp"
#include "gmath/transform/transform3D.hpp"

TEST_CASE("Transform2D_identity")
{
  auto const v = Vec2f{ 1, 1 };
  auto const result = Transform2D::IDENTITY * v;
  REQUIRE(result == v);
}

TEST_CASE("Transform2D_as_mat3")
{
  auto const transform = Transform2D{
    Mat2f::from_rows({ 1, 2, 3, 4 }
    ), Vec2f{ 1, 2 }
  };
  auto const M = transform.as_mat3();

  REQUIRE(M[0, 0] == 1);
  REQUIRE(M[0, 1] == 2);
  REQUIRE(M[0, 2] == 1);

  REQUIRE(M[1, 0] == 3);
  REQUIRE(M[1, 1] == 4);
  REQUIRE(M[1, 2] == 2);

  REQUIRE(M[2, 0] == 0);
  REQUIRE(M[2, 1] == 0);
  REQUIRE(M[2, 2] == 1);
}

TEST_CASE("Transform2D_rotation")
{
  auto const transform = Transform2D::rotate(Degf{ 90 });
  auto const v = Vec2f{ 1, 0 };
  auto const result = transform * v;
  REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE(result.y == Catch::Approx(1));
}

TEST_CASE("Transform2D_uniform_scale")
{
  auto const transform = Transform2D::scale(2.0);
  auto const v = Vec2f{ 1, -1 };
  auto const result = transform * v;
  REQUIRE(result == Vec2f{ 2, -2 });
}

TEST_CASE("Transform2D_non_uniform_scale")
{
  auto const transform = Transform2D::scale({ 2.0, 3.0 });
  auto const v = Vec2f{ 1, -1 };
  auto const result = transform * v;
  REQUIRE(result == Vec2f{ 2, -3 });
}

TEST_CASE("Transform2D_translation")
{
  auto const transform = Transform2D::translate({ 1, -1 });
  auto const p = Point2f{ 1, 1 };
  auto const result = transform * p;
  REQUIRE(result == Point2f{ 2, 0 });
}

TEST_CASE("Transform2D_skew_vector")
{
  auto const transform = Transform2D::skew(
      Degf{ 45 }, UVec2f::normalize(1, 0), UVec2f::normalize(0, 1));
  auto const v = Vec2f{ 0, 1 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(1));
  REQUIRE(result.y == Catch::Approx(1));
}

TEST_CASE("Transform2D_vectors_are_not_translated")
{
  auto const transform = Transform2D::translate({ 1, -1 });
  auto const v = Vec2f{ 1, 1 };
  auto const result = transform * v;
  REQUIRE(result == Vec2f{ 1, 1 });
}

TEST_CASE("Transform2D_combine_transformations_on_vectors")
{
  auto const transform
      = Transform2D::scale({ 3, 5 }) * Transform2D::rotate(Degf{ 90 });
  auto const v = Vec2f{ 1, 1 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(-3));
  REQUIRE(result.y == Catch::Approx(5));
}

TEST_CASE("Transform2D_combine_transformations_on_points")
{
  auto const transform = Transform2D::scale({ 9, 5 })
                         * Transform2D::rotate(Degf{ 90 })
                         * Transform2D::translate({ -1, 0 });
  auto const p = Point2f{ 5, -1 };
  auto const result = transform * p;
  REQUIRE(result.x == Catch::Approx(9));
  REQUIRE(result.y == Catch::Approx(20));
}

TEST_CASE("Transform2D_inverse_vector")
{
  auto const transform = Transform2D::rotate(Degf{ 45 })
                         * Transform2D::translate({ 1, 1 })
                         * Transform2D::scale({ 3, 5 });
  auto const v = Vec2f{ 1, 1 };
  auto const v1 = transform.inverse() * transform * v;
  REQUIRE(v1.x == Catch::Approx(1));
  REQUIRE(v1.y == Catch::Approx(1));
}

TEST_CASE("Transform2D_inverse_point")
{
  auto const transform = Transform2D::rotate(Degf{ 45 })
                         * Transform2D::translate({ 1, 1 })
                         * Transform2D::scale({ 3, 5 });
  auto const v = Point2f{ 1, 1 };
  auto const v1 = transform.inverse() * transform * v;
  REQUIRE(v1.x == Catch::Approx(1));
  REQUIRE(v1.y == Catch::Approx(1));
}

TEST_CASE("Transform3D_identity")
{
  auto const v = Vec3f{ 1, 1, 1 };
  auto const result = Transform3D::IDENTITY * v;
  REQUIRE(result == v);
}

TEST_CASE("Transform3D_as_mat4")
{
  auto const transform = Transform3D{
    Mat3f::from_rows({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    ), Vec3f{ 1, 2, 3 }
  };
  auto const M = transform.as_mat4();

  REQUIRE(M[0, 0] == 1);
  REQUIRE(M[0, 1] == 2);
  REQUIRE(M[0, 2] == 3);
  REQUIRE(M[0, 3] == 1);

  REQUIRE(M[1, 0] == 4);
  REQUIRE(M[1, 1] == 5);
  REQUIRE(M[1, 2] == 6);
  REQUIRE(M[1, 3] == 2);

  REQUIRE(M[2, 0] == 7);
  REQUIRE(M[2, 1] == 8);
  REQUIRE(M[2, 2] == 9);
  REQUIRE(M[2, 3] == 3);

  REQUIRE(M[3, 0] == 0);
  REQUIRE(M[3, 1] == 0);
  REQUIRE(M[3, 2] == 0);
  REQUIRE(M[3, 3] == 1);
}

TEST_CASE("Transform3D_x_axis_rotation")
{
  auto const transform = Transform3D::rotate(
      Degf{ 90 }, UVec3f::create_unchecked(1.f, 0.f, 0.f));
  auto const v = Vec3f{ 0, 1, 0 };
  auto const result = transform * v;
  REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE_THAT(result.y, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE(result.z == Catch::Approx(1));
}

TEST_CASE("Transform3D_z_axis_rotation")
{
  auto const transform = Transform3D::rotate(
      Degf{ 90 }, UVec3f::create_unchecked(0.f, 0.f, 1.f));
  auto const v = Vec3f{ 1, 0, 0 };
  auto const result = transform * v;
  REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE(result.y == Catch::Approx(1));
  REQUIRE_THAT(result.z, Catch::Matchers::WithinAbs(0, 0.0001));
}

TEST_CASE("Transform3D_y_axis_rotation")
{
  auto const transform = Transform3D::rotate(
      Degf{ 90 }, UVec3f::create_unchecked(0.f, 1.f, 0.f));
  auto const v = Vec3f{ 1, 0, 0 };
  auto const result = transform * v;
  REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE_THAT(result.y, Catch::Matchers::WithinAbs(0, 0.0001));
  REQUIRE(result.z == Catch::Approx(-1));
}

TEST_CASE("Transform3D_rotation_by_arbitrary_axis")
{
  auto const transform
      = Transform3D::rotate(Degf{ 90 }, UVec3f::normalize(2.f, -3.f, 4.f));
  auto const v = Vec3f{ 1, 5, 2 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(-5.17290));
  REQUIRE(result.y == Catch::Approx(0.517241));
  REQUIRE(result.z == Catch::Approx(1.724384));
}

TEST_CASE("Transform3D_uniform_scale")
{
  auto const transform = Transform3D::scale(2.0);
  auto const v = Vec3f{ 1, -1, 1 };
  auto const result = transform * v;
  REQUIRE(result == Vec3f{ 2, -2, 2 });
}

TEST_CASE("Transform3D_non_uniform_scale")
{
  auto const transform = Transform3D::scale({ 2.0, 3.0, 4.0 });
  auto const v = Vec3f{ 1, -1, 1 };
  auto const result = transform * v;
  REQUIRE(result == Vec3f{ 2, -3, 4 });
}

TEST_CASE("Transform3D_vectors_are_not_translated")
{
  auto const transform = Transform3D::translate({ 1, -1, 1 });
  auto const v = Vec3f{ 1, 1, 1 };
  auto const result = transform * v;
  REQUIRE(result == Vec3f{ 1, 1, 1 });
}

TEST_CASE("Transform3D_translates_points")
{
  auto const transform = Transform3D::translate({ 1, -1, 1 });
  auto const p = Point3f{ 1, 1, 1 };
  auto const result = transform * p;
  REQUIRE(result == Point3f{ 2, 0, 2 });
}

TEST_CASE("Transform3D_skew_vector")
{
  auto const transform = Transform3D::skew(
      Degf{ 45 }, UVec3f::normalize(1, 0, 0), UVec3f::normalize(0, 1, 0));
  auto const v = Vec3f{ 0, 1, 0 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(1));
  REQUIRE(result.y == Catch::Approx(1));
  REQUIRE_THAT(result.z, Catch::Matchers::WithinAbs(0, 0.0001));
}

TEST_CASE("Transform3D_reflect_vector")
{
  auto const plane = NormalizedPlane::from_plane(Plane{
      { 1, 1, 1 },
      0
  });
  auto const transform = Transform3D::reflect(plane);
  auto const v = Vec3f{ 1, 1, 1 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(-1));
  REQUIRE(result.y == Catch::Approx(-1));
  REQUIRE(result.z == Catch::Approx(-1));
}

TEST_CASE("Transform3D_combine_transformations_on_vectors")
{
  auto const transform = Transform3D::scale({ 3, 5, 7 })
                         * Transform3D::rotate(Degf{ 90 },
                             UVec3f::create_unchecked(1.f, 0.f, 0.f));
  auto const v = Vec3f{ 3, 8, -1 };
  auto const result = transform * v;
  REQUIRE(result.x == Catch::Approx(9));
  REQUIRE(result.y == Catch::Approx(5));
  REQUIRE(result.z == Catch::Approx(56));
}

TEST_CASE("Transform3D_combine_transformations_on_points")
{
  auto const transform = Transform3D::scale({ 9, 5, 7 })
                         * Transform3D::rotate(Degf{ 45 },
                             UVec3f::create_unchecked(0.f, 0.f, 1.f))
                         * Transform3D::translate({ -1, 0, 1 });
  auto const p = Point3f{ 5, -1, 3 };
  auto const result = transform * p;
  REQUIRE(result.x == Catch::Approx(31.81985));
  REQUIRE(result.y == Catch::Approx(10.6066));
  REQUIRE(result.z == Catch::Approx(28));
}

TEST_CASE("Transform3D_inverse_vector")
{
  auto const transform
      = Transform3D::rotate(Degf{ 45 }, UVec3f::normalize(1.f, 1.f, 1.f))
        * Transform3D::translate({ 1, 1, 1 })
        * Transform3D::scale({ 3, 5, 7 });
  auto const v = Vec3f{ 1, 1, 1 };
  auto const v1 = transform.inverse() * transform * v;
  REQUIRE(v1.x == Catch::Approx(1));
  REQUIRE(v1.y == Catch::Approx(1));
  REQUIRE(v1.z == Catch::Approx(1));
}

TEST_CASE("Transform3D_inverse_point")
{
  auto const transform
      = Transform3D::rotate(Degf{ 45 }, UVec3f::normalize(1.f, 1.f, 1.f))
        * Transform3D::translate({ 1, 1, 1 })
        * Transform3D::scale({ 3, 5, 7 });
  auto const v = Point3f{ 1, 1, 1 };
  auto const v1 = transform.inverse() * transform * v;
  REQUIRE(v1.x == Catch::Approx(1));
  REQUIRE(v1.y == Catch::Approx(1));
  REQUIRE(v1.z == Catch::Approx(1));
}

TEST_CASE("Transform3D_normals")
{
  auto const transform
      = Transform3D::rotate(Degf{ 45 }, UVec3f::normalize(1.f, 1.f, 1.f))
        * Transform3D::translate({ 1, 1, 1 })
        * Transform3D::scale({ 3, 5, 7 });
  auto const n = Normal3f{ 1, 1, 1 };
  auto const n_res = n * transform;
  auto const v = Vec3f{ 1, 1, 1 };
  auto const v_res = transpose(transform.matrix) * v;
  REQUIRE(n_res.x == Catch::Approx(v_res.x));
  REQUIRE(n_res.y == Catch::Approx(v_res.y));
  REQUIRE(n_res.z == Catch::Approx(v_res.z));
}
