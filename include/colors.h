#ifndef _color_h_
#define _color_h_

#include "functions.h"

using namespace std;

//–––––––––––––––––––––– Struct Color –––––––––––––––––––––––––––––––––––

struct Color {

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
  
  bool is_close(Color c) {
    return are_close(r, c.r) && are_close(g, c.g) && are_close(b, c.b);
  }

  float luminosity() { return (fmax(fmax(r, g), b) + fmin(fmin(r, g), b)) / 2.0; }
};

//––––––––––––––––––––– Color white and black ––––––––––––––––––––––––––––––––––

#define WHITE Color(1.0, 1.0, 1.0)
#define BLACK Color(0.0, 0.0, 0.0)
 
#endif

