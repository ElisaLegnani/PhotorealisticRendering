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

/**
 An abstract struct reprensenting the observer point of view.
 The observer sees the world as through a screen, where a 3D to 2D projection need to be applied on the base of the substruct.
 
 Substructs shared parameters:
 @param transformation to apply to the camera
 @param aspect_ratio a ratio between image width and height (important for the final visual effect)
 */
struct Camera {

  Transformation transformation;
  float aspect_ratio;

  Camera(float a = 1.0, Transformation t = Transformation()) : aspect_ratio{a}, transformation{t} {}
  
  /**
   Fire a ray though the camera screen
   
   Vec2d parameters (u,v) identify the screen position and are computed differently on the base of the substructs:
   @param u
   @param v
   */
  virtual Ray fire_ray(float, float) = 0;
};

/**
 A camera where the screen projection is the orthogonal one
 */
struct OrthogonalCamera : public Camera {

  OrthogonalCamera(float a = 1.0, Transformation t = Transformation()) : Camera(a, t) {}
  
  /**
   Fire a ray though the camera screen
   
   Vec2d parameters (u,v) identify the screen position:
   @param u
   @param v
   
   @return ray that crosses the screen
   */
  Ray fire_ray(float u, float v){
    Point o = Point(-1.0, (1.0-2.0*u)*aspect_ratio, 2.0*v-1.0);
    Vec d = VEC_X;
    return Ray(o, d, 1.0, INFINITY, 0).transform(transformation);
  }
};

/**
 A camera where the screen projection is the perspective one
 
 Additional parameter:
 @param screen_distance distance between the observer eye and the screen (needed for computing the "aperture")
 */
struct PerspectiveCamera : public Camera {

  float screen_dist;

  PerspectiveCamera(float d = 1.0, float a = 1.0, Transformation t = Transformation()) : screen_dist{d}, Camera(a, t) {}
  
  /**
   Fire a ray though the camera screen
   
   Vec2d parameters (u,v) identify the screen position:
   @param u
   @param v
   
   @return ray that crosses the screen
   */
  Ray fire_ray(float u, float v){
    Point o = Point(-screen_dist, 0.0, 0.0);
    Vec d = Vec(screen_dist, (1.0-2.0*u)*aspect_ratio, 2.0*v-1.0);
    return Ray(o, d, 1.0, INFINITY, 0).transform(transformation);
  }

  /**
   Return the aperture of the camera in degrees
  .
   The aperture is the field-of-view angle along the horizontal direction (Y axis)
   */
  float aperture_deg(){
    return 2.0 * atan(screen_dist/aspect_ratio) * 180.0 / M_PI;
  }
};


#endif
