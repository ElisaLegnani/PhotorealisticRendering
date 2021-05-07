#include "transformation.h"
#include "ray.h"

#ifndef _camera_h_
#define _camera_h_

struct Camera {
  virtual Ray fire_ray(float, float) = 0;
};

struct OrthogonalCamera : public Camera {
  Transformation transformation;
  float aspect_ratio;

  OrthogonalCamera(float a = 1.0, Transformation t = Transformation()) : aspect_ratio{a}, transformation{t} {}
  
  Ray fire_ray(float u, float v){
    Point o = Point(-1.0, (1.0-2.0*u)*aspect_ratio, 2.0*v-1.0);
    Vec d = VEC_X;
    return Ray(o, d, 1.0, INFINITY, 0).transform(transformation);
  }
};

struct PerspectiveCamera : public Camera {
  Transformation transformation;
  float aspect_ratio;
  float screen_dist;

  PerspectiveCamera(float d = 1.0, float a = 1.0, Transformation t = Transformation()) : screen_dist{d}, aspect_ratio{a}, transformation{t} {}
  
  Ray fire_ray(float u, float v){
    Point o = Point(-screen_dist, 0.0, 0.0);
    Vec d = Vec(screen_dist, (1.0-2.0*u)*aspect_ratio, 2.0*v-1.0);
    return Ray(o, d, 1.0, INFINITY, 0).transform(transformation);
  }

  float aperture_deg(){
    return 2.0 * atan(screen_dist/aspect_ratio) * 180.0 / M_PI;
  }
};


#endif
