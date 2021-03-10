#include "colors.h"
#include <cmath>

Color Color::operator+(Color c) {
  return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b);
}

Color Color::operator-(Color c) {
  return Color(m_r - c.m_r, m_g - c.m_g, m_b - c.m_b);
}

bool Color::are_colors_close(Color c1, Color c2) {
  return are_close(c1.m_r, c2.m_r) && are_close(c1.m_g, c2.m_g) &&
         are_close(c1.m_b, c2.m_b);
}

bool Color::are_close(float x, float y) {
  float epsilon = 1e-10;
  return abs(x - y) < epsilon;
}
