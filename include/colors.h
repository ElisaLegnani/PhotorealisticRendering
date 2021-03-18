#include <cmath>

#ifndef _color_h_
#define _color_h_

class Color {

public:
  Color() {
    m_r = 0.0;
    m_g = 0.0;
    m_b = 0.0;
  }

  Color(float r, float g, float b) {
    m_r = r;
    m_g = g;
    m_b = b;
  }

  ~Color(){};

  Color operator+(Color c) {
    return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b);
  }
  Color operator-(Color c) {
    return Color(m_r - c.m_r, m_g - c.m_g, m_b - c.m_b);
  }
  Color operator*(Color c) {
    return Color(m_r * c.m_r, m_g * c.m_g, m_b * c.m_b);
  }
  Color operator*(float x) { return Color(m_r * x, m_g * x, m_b * x); }

  bool is_color_close(Color c) {
    return are_close(m_r, c.m_r) && are_close(m_g, c.m_g) &&
           are_close(m_b, c.m_b);
  }

  bool are_close(float x, float y) {
    float epsilon = 1e-10;
    return abs(x - y) < epsilon;
  }

private:
  float m_r, m_g, m_b;
};

#endif