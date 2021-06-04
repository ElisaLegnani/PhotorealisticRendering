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
