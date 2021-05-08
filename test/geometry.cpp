#include "geometry.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// ––––––––––––––––– Test Vec –––––––––––––––––

Vec v1(1.0, 2.0, 3.0);
Vec v2(4.0, 6.0, 8.0);
Vec v3(v1);
Vec v4 = move(v1);

TEST_CASE("Vec constructor", "[vector]") {
  REQUIRE(v1.is_close(v1));
  REQUIRE(!v1.is_close(v2));
}

TEST_CASE("Vec copy constructor", "[vector]") { REQUIRE(v1.is_close(v3)); }

TEST_CASE("Vec move constructor", "[vector]") { REQUIRE(v1.is_close(v4)); }

/*v3=v2; // error:'v3’ does not name a type! perchè?

TEST_CASE( "Vec assignment operator", "[vector]" ) {
    REQUIRE( v2.is_close(v3) );
}*/

TEST_CASE("Vec operators", "[vector]") {
  REQUIRE((-v1).is_close(Vec(-1.0, -2.0, -3.0)));
  REQUIRE((v1 + v2).is_close(Vec(5.0, 8.0, 11.0)));
  REQUIRE((v2 - v1).is_close(Vec(3.0, 4.0, 5.0)));
  REQUIRE((2 * v1).is_close(Vec(2.0, 4.0, 6.0)));
  REQUIRE((v1 * 2).is_close(Vec(2.0, 4.0, 6.0)));
  REQUIRE(are_close(dot(v1, v2), 40.0));
  REQUIRE((cross(v1, v2)).is_close(Vec(-2.0, 4.0, -2.0)));
  REQUIRE((cross(v2, v1)).is_close(Vec(2.0, -4.0, 2.0)));
  REQUIRE(are_close(v1.squared_norm(), 14.0));
  REQUIRE(are_close(pow(v1.norm(), 2), 14.0));
}

// ––––––––––––––––– Test Point –––––––––––––––––

Point p1(1.0, 2.0, 3.0);
Point p2(4.0, 6.0, 8.0);
Point p3 = p1;
Point p4 = move(p1);

TEST_CASE("Point constructor", "[point]") {
  REQUIRE(p1.is_close(p1));
  REQUIRE(!p1.is_close(p2));
}

TEST_CASE("Point copy constructor", "[point]") { REQUIRE(p1.is_close(p3)); }

TEST_CASE("Point move constructor", "[point]") { REQUIRE(p1.is_close(p4)); }

/*p3=p2;

TEST_CASE( "Point assignment operator", "[point]" ) {
    REQUIRE( p2.is_close(p3) );
}*/

TEST_CASE("Point operators", "[point]") {
  REQUIRE((-p1).is_close(Point(-1.0, -2.0, -3.0)));
  REQUIRE((p1 * 2).is_close(Point(2.0, 4.0, 6.0)));
  REQUIRE((p1 + v2).is_close(Point(5.0, 8.0, 11.0)));
  REQUIRE((p2 - p1).is_close(Vec(3.0, 4.0, 5.0)));
  REQUIRE((p1 - v2).is_close(Point(-3.0, -4.0, -5.0)));
}

// –––––––– Test are_xyz_close (as template) ––––––––

TEST_CASE("are_xyz_close() with Vec", "[vector]") {
  REQUIRE(are_xyz_close(v1, v1));
  REQUIRE(!are_xyz_close(v1, v2));
}

TEST_CASE("Vec operators in are_xyz_close()", "[vector]") {
  REQUIRE(are_xyz_close((-v1), Vec(-1.0, -2.0, -3.0)));
  REQUIRE(are_xyz_close((v1 + v2), Vec(5.0, 8.0, 11.0)));
  REQUIRE(are_xyz_close((v2 - v1), Vec(3.0, 4.0, 5.0)));
  REQUIRE(are_xyz_close((2 * v1), Vec(2.0, 4.0, 6.0)));
  REQUIRE(are_xyz_close((v1 * 2), Vec(2.0, 4.0, 6.0)));
  REQUIRE(are_close(dot(v1, v2), 40.0));
  REQUIRE(are_xyz_close((cross(v1, v2)), Vec(-2.0, 4.0, -2.0)));
  REQUIRE(are_xyz_close((cross(v2, v1)), Vec(2.0, -4.0, 2.0)));
  REQUIRE(are_close(v1.squared_norm(), 14.0));
  REQUIRE(are_close(pow(v1.norm(),2), 14.0));
}

TEST_CASE("are_xyz_close() with Point", "[point]") {
  REQUIRE(are_xyz_close(p1, p1));
  REQUIRE(!are_xyz_close(p1, p2));
}

TEST_CASE("Point operators in are_xyz_close()", "[vector]") {
  REQUIRE(are_xyz_close((-p1), Point(-1.0, -2.0, -3.0)));
  REQUIRE(are_xyz_close((p1 * 2), Point(2.0, 4.0, 6.0)));
  REQUIRE(are_xyz_close((p1 + v2), Point(5.0, 8.0, 11.0)));
  REQUIRE(are_xyz_close((p2 - p1), Vec(3.0, 4.0, 5.0)));
  REQUIRE(are_xyz_close((p1 - v2), Point(-3.0, -4.0, -5.0)));
}

// ––––––––––––––––– Test Normal –––––––––––––––––

Normal n1(1.0, 2.0, 3.0);
Normal n2(4.0, 6.0, 8.0);
Normal n3(n1);
Normal n4 = move(n1);

TEST_CASE("Normal constructor", "[normal]") {
  REQUIRE(n1.is_close(n1));
  REQUIRE(!n1.is_close(n2));
}

TEST_CASE("Normal copy constructor", "[normal]") { REQUIRE(n1.is_close(n3)); }

TEST_CASE("Normal move constructor", "[normal]") { REQUIRE(n1.is_close(n4)); }

/*n3=n2;

TEST_CASE("Normal move constructor", "[normal]") {
  REQUIRE(n2.is_close(n3));
}*/