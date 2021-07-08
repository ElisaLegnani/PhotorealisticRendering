/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software. THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#ifndef _color_h_
#define _color_h_

#include "functions.h"
#include <iostream>

using namespace std;

//–––––––––––––––––––––– Struct Color –––––––––––––––––––––––––––––––––––
/**
 * A RGB color
 *
 * Floating-point parameters:
 * @param r red
 * @param g green
 * @param b blue
 */
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

  /**
   * An extimate of luminosity, evaluted as mean between the maximum and the minimum value
   */
  float luminosity() { return (fmax(fmax(r, g), b) + fmin(fmin(r, g), b)) / 2.0; }
  
  void print(){ cout << "Red: "<< r << ", Green: " << g << ", Blue: " <<b<<endl;}
};

//––––––––––––––––––––– Color white and black ––––––––––––––––––––––––––––––––––

#define WHITE Color(1.0, 1.0, 1.0)
#define BLACK Color(0.0, 0.0, 0.0)
 
#endif

