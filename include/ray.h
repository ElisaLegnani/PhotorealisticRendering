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
