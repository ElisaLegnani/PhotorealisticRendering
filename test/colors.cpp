/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
