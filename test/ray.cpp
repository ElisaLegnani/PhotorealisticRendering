#include "ray.h"
#include "catch_amalgamated.hpp"
#include "transformation.h"

#define CATCH_CONFIG_MAIN

Ray ray1(Point(1.0, 2.0, 3.0), Vec(5.0, 4.0, -1.0));
Ray ray2(Point(1.0, 2.0, 3.0), Vec(5.0, 4.0, -1.0));
Ray ray3(Point(5.0, 1.0, 4.0), Vec(3.0, 9.0, 4.0));

TEST_CASE("Ray constructor", "[ray]") {
  REQUIRE(ray1.is_close(ray2));
  REQUIRE(!ray1.is_close(ray3));
}

Ray ray4(Point(1.0, 2.0, 4.0), Vec(4.0, 2.0, 1.0));

TEST_CASE("Ray at", "[ray]") {
  REQUIRE(ray4.at(0.0).is_close(ray4.origin));
  REQUIRE(ray4.at(1.0).is_close(Point(5.0, 4.0, 5.0)));
  REQUIRE(ray4.at(2.0).is_close(Point(9.0, 6.0, 6.0)));
}

Ray ray5(Point(1.0, 2.0, 3.0), Vec(6.0, 5.0, 4.0));
Transformation tr = translation(Vec(10.0, 11.0, 12.0)) * rotation_x(90.0);
Ray transformed = ray5.transform(tr);

TEST_CASE("Ray transform", "[ray]") {
  REQUIRE(transformed.origin.is_close(Point(11.0, 8.0, 14.0)));
  REQUIRE(transformed.dir.is_close(Vec(6.0, -4.0, 5.0)));
}
