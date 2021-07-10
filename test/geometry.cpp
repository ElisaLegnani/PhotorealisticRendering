/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED “AS
IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "geometry.h"
#include "catch_amalgamated.hpp"
#include "pcg.h"

#define CATCH_CONFIG_MAIN

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

TEST_CASE("Vec assignment operator", "[vector]") {
  v3 = v2;
  REQUIRE(v2.is_close(v3));
}

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

TEST_CASE("Point assignment operator", "[point]") {
  p3 = p2;
  REQUIRE(p2.is_close(p3));
}

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
  REQUIRE(are_close(pow(v1.norm(), 2), 14.0));
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

TEST_CASE("Normal assignment operator", "[normal]") {
  n3 = n2;
  REQUIRE(n2.is_close(n3));
}

// ––––––––––––––––– Test ONB –––––––––––––––––

TEST_CASE("ONB constructor", "[onb]") {

  PCG pcg;

  for (int i{}; i < 100000; ++i) {
    Vec normal(pcg.random_float(), pcg.random_float(), pcg.random_float());
    normal.normalize();
    ONB onb(normal);

    REQUIRE(onb.e3.is_close(normal));

    REQUIRE(are_close(onb.e1.squared_norm(), 1.0));
    REQUIRE(are_close(onb.e2.squared_norm(), 1.0));
    REQUIRE(are_close(onb.e3.squared_norm(), 1.0));

    REQUIRE(are_close(dot(onb.e1, onb.e2), 0.0));
    REQUIRE(are_close(dot(onb.e2, onb.e3), 0.0));
    REQUIRE(are_close(dot(onb.e3, onb.e1), 0.0));
  }
}
