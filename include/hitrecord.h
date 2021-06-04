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
#include "ray.h"
#include "materials.h"
#include <string>

#ifndef _hitrecord_h_
#define _hitrecord_h_

/**
 * A struct containing information about a ray & shape intersection
 *
 * @param world_point
 * @param normal
 * @param surface_point
 * @param t
 * @param ray
 * @param material
 */
struct HitRecord {

  Point world_point;
  Normal normal;
  Vec2d surface_point;
  float t;
  Ray ray;
  Material material;
  bool init = false;

  HitRecord(){ init = false; }

  HitRecord(Point wp, Normal n, Vec2d sp, float T, Ray r)
      : world_point(wp), normal(n), surface_point(sp), t(T), ray(r) { init = true; }

  bool is_close(HitRecord hitrec) {
    return world_point.is_close(hitrec.world_point) &&
           normal.is_close(hitrec.normal) &&
           surface_point.is_close(hitrec.surface_point) &&
           are_close(t, hitrec.t) && ray.is_close(hitrec.ray);
  }
};

#endif
