#include "geometry.h"
#include "ray.h"

#ifndef _hitrecord_h_
#define _hitrecord_h_

/**
 * A 2D vector representing a point on a surface
 * with coordinates u, v
 */
struct Vec2d {

  float u = 0.0;
  float v = 0.0;

  bool is_close(Vec2d vec) {
    return are_close(x, vec.u) && are_close(y, vec.v);
  }
};

/**
 * A struct containing information about a ray & shape intersection
 * Parameters:
 *  - `world_point`
 *  - `normal`
 *  - `surface_point`
 *  - `t`
 *  - `ray`
 */
struct HitRecord {

  Point world_point;
  Normal normal;
  Vec2d surface_point;
  float t;
  Ray ray;

  bool is_close(Hitrecord hitrec) {
    return world_point.is_close(hitrec.world_point) &&
           normal.is_close(hitrec.normal) &&
           surface_point.is_close(hitrec.surface_point) &&
           are_close(t, hitrec.t) && ray.is_close(hitrec.ray);
  }
};

#endif
