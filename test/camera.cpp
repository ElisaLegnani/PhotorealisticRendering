#include "camera.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

// ––––––––––––––––– Test OrthogonalCamera –––––––––––––––––

OrthogonalCamera cam(2.0);

// Fire one ray for each corner of the image plane
Ray ray1 = cam.fire_ray(0.0, 0.0);
Ray ray2 = cam.fire_ray(1.0, 0.0);
Ray ray3 = cam.fire_ray(0.0, 1.0);
Ray ray4 = cam.fire_ray(1.0, 1.0);

// Verify that the rays are parallel by verifying that cross-products vanish
TEST_CASE("OrthogonalCamera: parallel rays", "[orthogonal camera]") {
  REQUIRE(are_close(0.0, cross(ray1.dir, ray2.dir).squared_norm()));
  REQUIRE(are_close(0.0, cross(ray1.dir, ray3.dir).squared_norm()));
  REQUIRE(are_close(0.0, cross(ray1.dir, ray4.dir).squared_norm()));
}

// Verify that the ray hitting the corners have the right coordinates
TEST_CASE("OrthogonalCamera: hitting coordinates", "[orthogonal camera]") {
  REQUIRE(ray1.at(1.0).is_close(Point(0.0, 2.0, -1.0)));
  REQUIRE(ray2.at(1.0).is_close(Point(0.0, -2.0, -1.0)));
  REQUIRE(ray3.at(1.0).is_close(Point(0.0, 2.0, 1.0)));
  REQUIRE(ray4.at(1.0).is_close(Point(0.0, -2.0, 1.0)));
}

// Test transform
Transformation tr = translation(-VEC_Y * 2.0) * rotation_z(90);
OrthogonalCamera cam2(1.0, tr);
Ray ray = cam2.fire_ray(0.5, 0.5);

TEST_CASE("OrthogonalCamera: transform", "[orthogonal camera]") {
  REQUIRE(ray.at(1.0).is_close(Point(0.0, -2.0, 0.0)));
}

// –––––––––––––––––  Test PerspectiveCamera –––––––––––––––––

PerspectiveCamera cam3(1.0, 2.0);

// Fire one ray for each corner of the image plane
Ray ray5 = cam3.fire_ray(0.0, 0.0);
Ray ray6 = cam3.fire_ray(1.0, 0.0);
Ray ray7 = cam3.fire_ray(0.0, 1.0);
Ray ray8 = cam3.fire_ray(1.0, 1.0);

// Verify that all the rays depart from the same point
TEST_CASE("PerspectiveCamera: rays depart from the same point",
          "[perspective camera]") {
  REQUIRE(ray5.origin.is_close(ray6.origin));
  REQUIRE(ray5.origin.is_close(ray7.origin));
  REQUIRE(ray5.origin.is_close(ray8.origin));
}

// Verify that the ray hitting the corners have the right coordinates
TEST_CASE("PerspectiveCamera: hitting coordinates", "[perspective camera]") {
  REQUIRE(ray5.at(1.0).is_close(Point(0.0, 2.0, -1.0)));
  REQUIRE(ray6.at(1.0).is_close(Point(0.0, -2.0, -1.0)));
  REQUIRE(ray7.at(1.0).is_close(Point(0.0, 2.0, 1.0)));
  REQUIRE(ray8.at(1.0).is_close(Point(0.0, -2.0, 1.0)));
}

// Test transform
Transformation tr2 = translation(-VEC_Y * 2.0) * rotation_z(90);
PerspectiveCamera cam4(1.0, 1.0, tr2);
Ray ray9 = cam4.fire_ray(0.5, 0.5);

TEST_CASE("PerspectiveCamera: transform", "[perspective camera]") {
  REQUIRE(ray9.at(1.0).is_close(Point(0.0, -2.0, 0.0)));
}