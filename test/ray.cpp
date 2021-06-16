/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software. THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

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
