#include "colors.h"
#include <cmath>

Color Color::operator+(Color c) {
  return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b);
}

Color Color::operator-(Color c) {
  return Color(m_r - c.m_r, m_g - c.m_g, m_b - c.m_b);
}

Color Color::operator*(Color c) {
  return Color(m_r * c.m_r, m_g * c.m_g, m_b * c.m_b);
}

Color Color::operator*(float x) { return Color(m_r * x, m_g * x, m_b * x); }

bool Color::is_color_close(Color c) {
  return are_close(m_r, c.m_r) && are_close(m_g, c.m_g) &&
         are_close(m_b, c.m_b);
}

bool Color::are_close(float x, float y) {
  float epsilon = 1e-10;
  return abs(x - y) < epsilon;
}
