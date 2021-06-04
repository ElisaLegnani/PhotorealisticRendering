#ifndef _functions_h_
#define _functions_h_

#include <cmath>

inline bool are_close(float x, float y, float epsilon = 1e-4) {
  return fabs(x - y) < epsilon;
}

#endif
