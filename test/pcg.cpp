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

#include "pcg.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("PCG", "[pcg]") {

  PCG pcg;

  REQUIRE(pcg.state == 1753877967969059832);
  REQUIRE(pcg.inc == 109);

  uint32_t expected[6] = {2707161783, 2068313097, 3122475824,
                          2211639955, 3215226955, 3421331566};

  for (int i{}; i < 6; ++i) {
    REQUIRE(expected[i] == pcg.random());
  }
}
