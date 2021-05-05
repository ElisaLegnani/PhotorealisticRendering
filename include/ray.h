#include "geometry.h"
#include <cmath>

#ifndef _ray_h_
#define _ray_h_

struct Ray {

  Point origin = Point();
  Vec dir = Vec();
  float tmin = 1e-5;
  float tmax = INFINITY;
  int depth = 0;

  Ray(Point o, Vec d) : origin{o}, dir{d} {}

  bool is_close(Ray r) {
    return origin.is_close(r.origin) && dir.is_close(r.dir);
  }

  Point at(float factor) { return origin + dir * factor; }
};

#endif
