#include "geometry.h"
#include "transformation.h"
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
