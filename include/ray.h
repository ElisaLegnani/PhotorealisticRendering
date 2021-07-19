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

/**
 A ray of light propagating in the space
 
 @param origin the 'Point' where the ray originates
 @param dir a 'Vec' to identify the direction of propagation
 @param tmin floating-point parameter identifing the "minimum distance" the ray travels (to be multiplied by 'dir', default 1e-5)
 @param tmax floating-point parameter identifing the "maximum distance" the ray travels (to be multiplied by 'dir', default INFINITY)
 @param depth integer parameter giving the number of reflections on surfaces (default 0)
 */
struct Ray {

  Point origin = Point();
  Vec dir = Vec();
  float tmin = 1e-5;
  float tmax = INFINITY;
  int depth = 0;

  Ray(){};
  Ray(Point o, Vec d) : origin{o}, dir{d} {}
  Ray(Point o, Vec d, float tm, float tM, int n) : origin{o}, dir{d} , tmin{tm}, tmax{tM}, depth{n} {}

  /**
   Check if the ray is close enough to the given one to be considered the same
   Needed to avoid floating-point approximation limits.
   */
  bool is_close(const Ray r) {
    return origin.is_close(r.origin) && dir.is_close(r.dir);
  }

  /**
   Return the point along the ray direction with the given "distance" factor from the origin (to be multiplied by 'dir')
   */
  Point at(const float factor) { return origin + dir * factor; }
  
  /**
   Return the transformed ray (origin and direction)
   */
  Ray transform(const Transformation T){
    Ray newray((T*origin), (T*dir), tmin, tmax, depth);
    return newray;
  }
};

#endif
