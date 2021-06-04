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

#include "materials.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("UniformPigment constructor", "[pigment]") {

  Color color(1.0, 2.0, 3.0);
  UniformPigment pigment(color);

  REQUIRE(pigment.get_color(Vec2d(0.0, 0.0)).is_close(color));
  REQUIRE(pigment.get_color(Vec2d(1.0, 0.0)).is_close(color));
  REQUIRE(pigment.get_color(Vec2d(0.0, 1.0)).is_close(color));
  REQUIRE(pigment.get_color(Vec2d(1.0, 1.0)).is_close(color));
}

TEST_CASE("ImagePigment constructor", "[pigment]") {

  HdrImage image(2, 2);
  image.set_pixel(0, 0, Color(1.0, 2.0, 3.0));
  image.set_pixel(1, 0, Color(2.0, 3.0, 1.0));
  image.set_pixel(0, 1, Color(2.0, 1.0, 3.0));
  image.set_pixel(1, 1, Color(3.0, 2.0, 1.0));

  ImagePigment pigment(image);
        
  REQUIRE(pigment.get_color(Vec2d(0.0, 0.0)).is_close(Color(1.0, 2.0, 3.0)));
  REQUIRE(pigment.get_color(Vec2d(1.0, 0.0)).is_close(Color(2.0, 3.0, 1.0)));
  REQUIRE(pigment.get_color(Vec2d(0.0, 1.0)).is_close(Color(2.0, 1.0, 3.0)));
  REQUIRE(pigment.get_color(Vec2d(1.0, 1.0)).is_close(Color(3.0, 2.0, 1.0)));
}

TEST_CASE("CheckeredPigment constructor", "[pigment]") {

  Color color1(1.0, 2.0, 3.0);
  Color color2(10.0, 20.0, 30.0);

  CheckeredPigment pigment(color1, color2, 2);
        
  REQUIRE(pigment.get_color(Vec2d(0.25, 0.25)).is_close(color1));
  REQUIRE(pigment.get_color(Vec2d(0.75, 0.25)).is_close(color2));
  REQUIRE(pigment.get_color(Vec2d(0.25, 0.75)).is_close(color2));
  REQUIRE(pigment.get_color(Vec2d(0.75, 0.75)).is_close(color1));
}
