#include "transformation.h"
#include "ray.h"

#ifndef _camera_h_
#define _camera_h_

inline Vec VEC_X(1.0, 0.0, 0.0);
inline Vec VEC_Y(0.0, 1.0, 0.0);
inline Vec VEC_Z(0.0, 0.0, 1.0);

struct Camera {
  virtual Ray fire_ray(float, float) = 0;
};

struct OrthogonalCamera : public Camera {
  Transformation transformation;
  float aspect_ratio;

  OrthogonalCamera(float a = 1.0, Transformation t = Transformation()) : aspect_ratio{a}, transformation{t} {}
  
  Ray fire_ray(float u, float v){
    Point o = Point();
    Vec d = VEC_X;
    return Ray(o, d, 1.0); //transformation
  }
};

#endif
