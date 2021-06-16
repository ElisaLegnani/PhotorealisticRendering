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
