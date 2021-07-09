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

#include "geometry.h"
#include "transformation.h"

#ifndef _ray_h_
#define _ray_h_

struct Ray {

  Point origin = Point();
  Vec dir = Vec();
  float tmin = 1e-5;
  float tmax = INFINITY;
  int depth = 0;

  Ray(){};
  Ray(Point o, Vec d) : origin{o}, dir{d} {}
  Ray(Point o, Vec d, float tm, float tM, int n) : origin{o}, dir{d} , tmin{tm}, tmax{tM}, depth{n} {}

  bool is_close(const Ray r) {
    return origin.is_close(r.origin) && dir.is_close(r.dir);
  }

  Point at(const float factor) { return origin + dir * factor; }
  
  Ray transform(const Transformation T){
    Ray newray((T*origin), (T*dir), tmin, tmax, depth);
    return newray;
  }
};

#endif
