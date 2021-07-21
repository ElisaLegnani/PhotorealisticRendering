/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

