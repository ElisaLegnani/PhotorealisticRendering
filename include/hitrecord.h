#include "geometry.h"
#include "ray.h"
#include <string>

#ifndef _hitrecord_h_
#define _hitrecord_h_

/**
 * A 2D vector representing a point on a surface
 * 
 * @param u
 * @param v
 */
struct Vec2d {

  float u;
  float v;
  
  Vec2d(float U=0.0, float V=0.0) : u(U),v(V){}

  bool is_close(Vec2d vec) {
    return are_close(u, vec.u) && are_close(v, vec.v);
  }
  string get_string(){
    return string{"Vec2d(" + to_string(u) + ", " + to_string(v) +")"};
  }
};

/**
 * A struct containing information about a ray & shape intersection
 *
 * @param world_point
 * @param normal
 * @param surface_point
 * @param t
 * @param ray
 */
struct HitRecord {

  Point world_point;
  Normal normal;
  Vec2d surface_point;
  float t;
  Ray ray;
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
