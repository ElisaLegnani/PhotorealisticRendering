# include "color.h"

bool are_close(float x, float y) {
  float epsilon = 1e-10;
  return abs(x - y) < epsilon;
}

