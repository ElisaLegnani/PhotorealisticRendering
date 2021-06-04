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

#include "colors.h"
#include <iostream>
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file

Color c1(1.0, 2.0, 3.0);
Color c2(5.0, 7.0, 9.0);
float x = 5.0;

TEST_CASE("Color operators", "[color]") {
  REQUIRE((c1 + c2).is_close(Color(6.0, 9.0, 12.0)));
  REQUIRE((c2 - c1).is_close(Color(4.0, 5.0, 6.0)));
  REQUIRE((c1 * c2).is_close(Color(5.0, 14.0, 27.0)));
  REQUIRE((c1 * x).is_close(Color(5.0, 10.0, 15.0)));
}

TEST_CASE("Color luminosity", "[color]") {
  REQUIRE(are_close(c1.luminosity(), 2));
  REQUIRE(are_close(c2.luminosity(), 7));
}
