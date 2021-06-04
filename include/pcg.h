#include <cstdint>

#ifndef _pcg_h_
#define _pcg_h_

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

  uint32_t random() {
    uint64_t oldstate = state;
    state = uint64_t(oldstate * 6364136223846793005 + inc);
    // "^" is the xor operation
    uint32_t xorshifted = uint32_t(((oldstate >> 18) ^ oldstate) >> 27);
    uint32_t rot = oldstate >> 59;

    return uint32_t((xorshifted >> rot) | (xorshifted << ((-rot) & 31)));
  }

  float random_float() {
    return random() / UINT32_MAX;
  }
};

#endif