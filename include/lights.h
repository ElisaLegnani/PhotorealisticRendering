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

#include "colors.h"
#include "geometry.h"

#ifndef _lights_h_
#define _lights_h_

//––––––––––––– Struct Point Light Source –––––––––––––––––––––––––

/** A struct representing a point light source
 *
 *@param position Point where is the light source
 *@param color of the light source
 *@param linear_radius used to compute the soild angle subtended by the light at distance d ( solid_angle=(r/d)^2 )
 */
struct PointLight{
  Point position;
  Color color;
  float linear_radius;
  
  PointLight(Point pos, Color c, float lr = 0.) : position{pos}, color{c}, linear_radius{lr} {}
  
  PointLight(const PointLight &pl): position{pl.position}, color{pl.color}, linear_radius{pl.linear_radius} {}
  
  
};

#endif
