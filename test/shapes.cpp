#include "shapes.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

  // Test hit

TEST_CASE("Shapes hit", "[shapes]") {
  Sphere sphere;
  Ray ray1(Point(0.0, 0.0, 2.0), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  REQUIRE(intersection1.init);
  REQUIRE(intersection1.is_close(HitRecord(Point(0.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0), Vec2d(0.0, 0.0), 1.0, ray1)));

  Ray ray2(Point(3, 0, 0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);

  REQUIRE(intersection2.init);
  REQUIRE(intersection2.is_close(HitRecord(Point(1.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.5), 2.0, ray2)));
  REQUIRE(!sphere.ray_intersection(Ray(Point(0, 10, 2), -VEC_Z)).init);
}
  // Test internal hit
TEST_CASE("Shapes internal hit", "[shapes]") {
  Sphere sphere;
  Ray ray(Point(0, 0, 0), VEC_X);
  HitRecord intersection = sphere.ray_intersection(ray);

  REQUIRE(intersection.init);
  REQUIRE(intersection.is_close(HitRecord(Point(1.0, 0.0, 0.0), Normal(-1.0, 0.0, 0.0),
                                Vec2d(0.0, 0.5), 1.0, ray)));
}
  // Test transformation
TEST_CASE("Shapes transformation", "[shapes]"){
  Sphere sphere(translation(Vec(10.0, 0.0, 0.0)));
  Ray ray1(Point(10, 0, 2), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  REQUIRE(intersection1.init);
  REQUIRE(intersection1.is_close(HitRecord(Point(10.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0),
                                          Vec2d(0.0, 0.0), 1.0, ray1)));

  Ray ray2(Point(13, 0, 0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);
  
  INFO(intersection2.world_point.get_string());
  INFO(intersection2.normal.get_string());
  INFO(intersection2.surface_point.get_string());
  INFO(intersection2.t);
  
  REQUIRE(intersection2.init);
  REQUIRE(intersection2.is_close(HitRecord(Point(11.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.0), 2.0, ray2)));


  //  -----------------------------------------Questo test fallisce su MAC!
  /*test_closeness(intersection5, HitRecord(Point(11.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.0), 2.0, ray5));*/

  // Check if the sphere failed to move by trying to hit the untransformed shape
  REQUIRE(!sphere.ray_intersection(Ray(Point(0, 0, 2), -VEC_Z)).init);

  // Check if the *inverse* transformation was wrongly applied
  REQUIRE(!sphere.ray_intersection(Ray(Point(-10, 0, 0), -VEC_Z)).init);
}

  // Test normals
  TEST_CASE("Shapes normal", "[shapes]"){
    
  Sphere sphere(scaling(Vec(2.0, 1.0, 1.0)));
  Ray ray(Point(1.0, 1.0, 0.0), Vec(-1.0, -1.0));
  HitRecord intersection = sphere.ray_intersection(ray);

  // We normalize "intersection.normal", as we are not interested in its length
    REQUIRE(intersection.normal.normalize().is_close(Normal(1.0, 4.0, 0.0).normalize()));
  }
  // Test normal direction
TEST_CASE("Shapes normal direction", "[shapes]"){
  // Scaling a sphere by -1 keeps the sphere the same but reverses its reference frame
  Sphere sphere(scaling(Vec(-1.0, -1.0, -1.0)));
  Ray ray(Point(0.0, 2.0, 0.0), -VEC_Y);
  HitRecord intersection = sphere.ray_intersection(ray);
  
  REQUIRE(intersection.normal.normalize().is_close(Normal(0.0, 1.0, 0.0).normalize()));
}
  // Test uv coordinates
TEST_CASE("Shapes uv coordinates", "[shapes]"){
  Sphere sphere;

  Ray ray1(Point(2.0, 0.0, 0.0), -VEC_X);
  REQUIRE(sphere.ray_intersection(ray1).surface_point.is_close(Vec2d(0.0, 0.5)));

  Ray ray2(Point(0.0, 2.0, 0.0), -VEC_Y);
  REQUIRE(sphere.ray_intersection(ray2).surface_point.is_close(Vec2d(0.25, 0.5)));

  Ray ray3(Point(-2.0, 0.0, 0.0), VEC_X);
  REQUIRE(sphere.ray_intersection(ray3).surface_point.is_close(Vec2d(0.5, 0.5)));

  //  -----------------------------------------Questo test fallisce su MAC!
  Ray ray4(Point(0.0, -2.0, 0.0), -VEC_Y);
  HitRecord intersection2=sphere.ray_intersection(ray4);
  INFO(intersection2.world_point.get_string());
  INFO(intersection2.normal.get_string());
  INFO(intersection2.surface_point.get_string());
  INFO(intersection2.t);
  REQUIRE(intersection2.surface_point.is_close(Vec2d(0.75, 0.5)));

  Ray ray5(Point(2.0, 0.0, 0.5), -VEC_X);
    REQUIRE(sphere.ray_intersection(ray5).surface_point.is_close(Vec2d(0.0, 1/3)));

  Ray ray6(Point(2.0, 0.0, -0.5), -VEC_X);
  REQUIRE(sphere.ray_intersection(ray6).surface_point.is_close(Vec2d(0.0, 2/3)));
}
