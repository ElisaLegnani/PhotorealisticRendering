#include "shapes.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

// –––––––––––––––––  Test Sphere –––––––––––––––––

TEST_CASE("Sphere: Hit", "[sphere]") {
  Sphere sphere;
  Ray ray1(Point(0.0, 0.0, 2.0), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  REQUIRE(intersection1.init);
  REQUIRE(sphere.check_if_intersection(ray1));
  REQUIRE(intersection1.is_close(HitRecord(Point(0.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0), Vec2d(0.0, 0.0), 1.0, ray1)));

  Ray ray2(Point(3, 0, 0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);

  REQUIRE(intersection2.init);
  REQUIRE(sphere.check_if_intersection(ray2));
  REQUIRE(intersection2.is_close(HitRecord(Point(1.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.5), 2.0, ray2)));
  
  REQUIRE(!sphere.ray_intersection(Ray(Point(0, 10, 2), -VEC_Z)).init);
  REQUIRE(!sphere.check_if_intersection(Ray(Point(0, 10, 2), -VEC_Z)));
}

TEST_CASE("Sphere: Internal Hit", "[sphere]") {
  Sphere sphere;
  Ray ray(Point(0, 0, 0), VEC_X);
  HitRecord intersection = sphere.ray_intersection(ray);

  REQUIRE(intersection.init);
  REQUIRE(intersection.is_close(HitRecord(Point(1.0, 0.0, 0.0), Normal(-1.0, 0.0, 0.0),
                                Vec2d(0.0, 0.5), 1.0, ray)));
}

TEST_CASE("Sphere: Transformation", "[sphere]"){
  Sphere sphere(translation(Vec(10.0, 0.0, 0.0)));
  Ray ray1(Point(10, 0, 2), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  REQUIRE(intersection1.init);
  REQUIRE(intersection1.is_close(HitRecord(Point(10.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0),
                                          Vec2d(0.0, 0.0), 1.0, ray1)));

  Ray ray2(Point(13.0, 0.0, 0.0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);
  
  REQUIRE(intersection2.init);
  REQUIRE(intersection2.is_close(HitRecord(Point(11.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.5), 2.0, ray2)));

  // Check if the sphere failed to move by trying to hit the untransformed shape
  REQUIRE(!sphere.ray_intersection(Ray(Point(0, 0, 2), -VEC_Z)).init);

  // Check if the *inverse* transformation was wrongly applied
  REQUIRE(!sphere.ray_intersection(Ray(Point(-10, 0, 0), -VEC_Z)).init);
}

  TEST_CASE("Sphere: Normals", "[sphere]"){
    
  Sphere sphere(scaling(Vec(2.0, 1.0, 1.0)));
  Ray ray(Point(1.0, 1.0, 0.0), Vec(-1.0, -1.0));
  HitRecord intersection = sphere.ray_intersection(ray);

  // We normalize "intersection.normal", as we are not interested in its length
    REQUIRE(intersection.normal.normalize().is_close(Normal(1.0, 4.0, 0.0).normalize()));
  }

TEST_CASE("Sphere: Normal Direction", "[sphere]"){
  // Scaling a sphere by -1 keeps the sphere the same but reverses its reference frame
  Sphere sphere(scaling(Vec(-1.0, -1.0, -1.0)));
  Ray ray(Point(0.0, 2.0, 0.0), -VEC_Y);
  HitRecord intersection = sphere.ray_intersection(ray);
  
  REQUIRE(intersection.normal.normalize().is_close(Normal(0.0, 1.0, 0.0).normalize()));
}

TEST_CASE("Sphere: uv coordinates", "[sphere]"){
  Sphere sphere;

  Ray ray1(Point(2.0, 0.0, 0.0), -VEC_X); //P1 (1.,0.,0.)
  REQUIRE(sphere.ray_intersection(ray1).surface_point.is_close(Vec2d(0.0, 0.5)));

  Ray ray2(Point(0.0, 2.0, 0.0), -VEC_Y); //P2 (0.,1.,0.)
  REQUIRE(sphere.ray_intersection(ray2).surface_point.is_close(Vec2d(0.25, 0.5)));

  Ray ray3(Point(-2.0, 0.0, 0.0), VEC_X); //P3 (-1.,0.,0.)
  REQUIRE(sphere.ray_intersection(ray3).surface_point.is_close(Vec2d(0.5, 0.5)));

  Ray ray4(Point(0.0, -2.0, 0.0), VEC_Y); //P4 (0.,-1.,0.)
  REQUIRE(sphere.ray_intersection(ray4).surface_point.is_close(Vec2d(0.75, 0.5)));

  Ray ray5(Point(2.0, 0.0, 0.5), -VEC_X); //P5 (1.,0.,0.5)
  REQUIRE(sphere.ray_intersection(ray5).surface_point.is_close(Vec2d(0.0, 1. / 3)));

  Ray ray6(Point(2.0, 0.0, -0.5), -VEC_X); //P6 (1.,0.,-0.5)
  REQUIRE(sphere.ray_intersection(ray6).surface_point.is_close(Vec2d(0.0, 2./3)));
}

// –––––––––––––––––  Test Plane –––––––––––––––––

TEST_CASE("Plane: Hit", "[plane]"){
  Plane plane;
  Ray ray1(Point(0, 0, 1), -VEC_Z);
  HitRecord intersection1 = plane.ray_intersection(ray1);
  
  REQUIRE(intersection1.init);
  REQUIRE(plane.check_if_intersection(ray1));
  REQUIRE(intersection1.is_close(HitRecord(Point(0.0, 0.0, 0.0), Normal(0.0, 0.0, 1.0), Vec2d(0.0, 0.0), 1.0, ray1)));
  
  Ray ray2(Point(0, 0, 1), VEC_Z);
  HitRecord intersection2 = plane.ray_intersection(ray2);
  REQUIRE(!intersection2.init);
  REQUIRE(!plane.check_if_intersection(ray2));

  Ray ray3(Point(0, 0, 1), VEC_X);
  HitRecord intersection3 = plane.ray_intersection(ray3);
  REQUIRE(!intersection3.init);
  REQUIRE(!plane.check_if_intersection(ray3));

  Ray ray4(Point(0, 0, 1), VEC_Y);
  HitRecord intersection4 = plane.ray_intersection(ray4);
  REQUIRE(!intersection4.init);
  REQUIRE(!plane.check_if_intersection(ray4));
}

TEST_CASE("Plane: Transformation", "[plane]"){
  Plane plane(rotation_y(90.));

  Ray ray1(Point(1, 0, 0), -VEC_X);
  HitRecord intersection1 = plane.ray_intersection(ray1);
  REQUIRE(intersection1.init);
  REQUIRE(intersection1.is_close(HitRecord(Point(0.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.0), 1.0, ray1)));

  Ray ray2(Point(0, 0, 1), VEC_Z);
  HitRecord intersection2 = plane.ray_intersection(ray2);
  REQUIRE(!intersection2.init);
  REQUIRE(!plane.check_if_intersection(ray2));

  Ray ray3(Point(0, 0, 1), VEC_X);
  HitRecord intersection3 = plane.ray_intersection(ray3);
  REQUIRE(!intersection3.init);
  REQUIRE(!plane.check_if_intersection(ray3));

  Ray ray4(Point(0, 0, 1), VEC_Y);
  HitRecord intersection4 = plane.ray_intersection(ray4);
  REQUIRE(!intersection4.init);
  REQUIRE(!plane.check_if_intersection(ray4));
}

TEST_CASE("Plane: uv coordinates", "[plane]"){
  Plane plane;

  Ray ray1(Point(0, 0, 1), -VEC_Z);
  HitRecord intersection1 = plane.ray_intersection(ray1);
  REQUIRE(intersection1.surface_point.is_close(Vec2d(0.0, 0.0)));

  Ray ray2(Point(0.25, 0.75, 1), -VEC_Z);
  HitRecord intersection2 = plane.ray_intersection(ray2);
  REQUIRE(intersection2.surface_point.is_close(Vec2d(0.25, 0.75)));

  Ray ray3(Point(4.25, 7.75, 1), -VEC_Z);
  HitRecord intersection3 = plane.ray_intersection(ray3);
  REQUIRE(intersection3.surface_point.is_close(Vec2d(0.25, 0.75)));
}
