#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

#ifndef _color_h_
#define _color_h_

class Color {

public:
  float r, g, b;

  Color() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
  }

  Color(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
  }

  ~Color(){};

//  Operations on Colors
  
  Color operator+(Color c) { return Color(r + c.r, g + c.g, b + c.b); }
  Color operator-(Color c) { return Color(r - c.r, g - c.g, b - c.b); }
  Color operator*(Color c) { return Color(r * c.r, g * c.g, b * c.b); }
  Color operator*(float x) { return Color(r * x, g * x, b * x); }

//  Similarity level: need for test porpuse
  
  bool is_color_close(Color c) {
    return are_close(r, c.r) && are_close(g, c.g) && are_close(b, c.b);
  }

  bool are_close(float x, float y) {
    float epsilon = 1e-10;
    return abs(x - y) < epsilon;
  }

  float luminosity() { return (max(max(r, g), b) + min(min(r, g), b)) / 2.0; }
};

#endif
