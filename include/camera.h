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

#include "transformation.h"
#include "ray.h"

#ifndef _camera_h_
#define _camera_h_

struct Camera {

  Transformation transformation;
  float aspect_ratio;

  Camera(float a = 1.0, Transformation t = Transformation()) : aspect_ratio{a}, transformation{t} {}

  virtual Ray fire_ray(float, float) = 0;
};

struct OrthogonalCamera : public Camera {

  OrthogonalCamera(float a = 1.0, Transformation t = Transformation()) : Camera(a, t) {}
  
  Ray fire_ray(float u, float v){
    Point o = Point(-1.0, (1.0-2.0*u)*aspect_ratio, 2.0*v-1.0);
    Vec d = VEC_X;
    return Ray(o, d, 1.0, INFINITY, 0).transform(transformation);
  }
};

struct PerspectiveCamera : public Camera {

  float screen_dist;

  PerspectiveCamera(float d = 1.0, float a = 1.0, Transformation t = Transformation()) : screen_dist{d}, Camera(a, t) {}
  
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
