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

#include <cstdint>

#ifndef _pcg_h_
#define _pcg_h_

/**
 * A class implementing a PCG pseudo-random number generator
 *
 * @param state
 * @param inc
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

  /** Returns a new random number and advances PCG's state */
  uint32_t random() {
    uint64_t oldstate = state;
    state = uint64_t(oldstate * 6364136223846793005 + inc);
    // "^" is the xor operation
    uint32_t xorshifted = uint32_t(((oldstate >> 18) ^ oldstate) >> 27);
    uint32_t rot = oldstate >> 59;

    return uint32_t((xorshifted >> rot) | (xorshifted << ((-rot) & 31)));
  }

  /** Returns a random number uniformly distributed over [0,1] */
  float random_float() {
    return random() / float(0xffffffff);
  }
};

#endif
