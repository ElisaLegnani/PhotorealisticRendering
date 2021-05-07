#ifndef _functions_h_
#define _functions_h_

#include <algorithm>

inline bool are_close(float x, float y, float epsilon = 1e-4) {
  return abs(x - y) < epsilon;
}

#endif
