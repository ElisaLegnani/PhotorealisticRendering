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
