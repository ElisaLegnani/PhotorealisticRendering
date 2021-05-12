#include "colors.h"
#include <iostream>
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file

Color c1(1.0, 2.0, 3.0);
Color c2(5.0, 7.0, 9.0);
float x = 5.0;

TEST_CASE("Color operators", "[color]") {
  REQUIRE((c1 + c2).is_color_close(Color(6.0, 9.0, 12.0)));
  REQUIRE((c2 - c1).is_color_close(Color(4.0, 5.0, 6.0)));
  REQUIRE((c1 * c2).is_color_close(Color(5.0, 14.0, 27.0)));
  REQUIRE((c1 * x).is_color_close(Color(5.0, 10.0, 15.0)));
}

TEST_CASE("Color luminosity", "[color]") {
  REQUIRE(are_close(c1.luminosity(), 2));
  REQUIRE(are_close(c2.luminosity(), 7));
}