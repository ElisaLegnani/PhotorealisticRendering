#include "colors.h"
#include <cmath>

Color Color::sum_colors(Color c1, Color c2) {
  return Color(c1.m_r + c2.m_r, c1.m_g + c2.m_g, c1.m_b + c2.m_b);
}

bool Color::are_colors_close(Color c1, Color c2) {
  return are_close(c1.m_r, c2.m_r) && are_close(c1.m_g, c2.m_g) &&
         are_close(c1.m_b, c2.m_b);
}

bool Color::are_close(float x, float y) {
  float epsilon = 1e-10;
  return abs(x - y) < epsilon;
}
