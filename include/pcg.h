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

#include <cstdint>

#ifndef _pcg_h_
#define _pcg_h_

/**
 * A class implementing a PCG pseudo-random number generator
 *
 * @param state initial seed (default 42)
 * @param inc identifier of the sequence (default 54)
 */
class PCG {

public:

  uint64_t state = 0;
  uint64_t inc = 0;

  PCG(uint64_t init_state = 42, uint64_t init_seq = 54) {
    inc = (init_seq << 1) | 1;
    random();
    state += init_state;
    random();
  }

  /**
   * Return a new random number, advancing the PCG's internal state
   */
  uint32_t random() {
    uint64_t oldstate = state;
    state = uint64_t(oldstate * 6364136223846793005 + inc);
    // "^" is the xor operation
    uint32_t xorshifted = uint32_t(((oldstate >> 18) ^ oldstate) >> 27);
    uint32_t rot = oldstate >> 59;

    return uint32_t((xorshifted >> rot) | (xorshifted << ((-rot) & 31)));
  }

  /**
   * Return a random number uniformly distributed over [0,1]
   */
  float random_float() {
    return random() / float(0xffffffff);
  }
};

#endif
