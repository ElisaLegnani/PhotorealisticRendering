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
#include "ray.h"
#include "materials.h"
#include <string>

#ifndef _shapes_h_
#define _shapes_h_

//––––––––––––– Functions for sub-Struct Sphere –––––––––––––––––––––––––

/** Converts a 3D sphere point to 2D (u,v) coordinates */
Vec2d _sphere_point_to_uv(Point);

/**
 Evaluates the normal of the sphere in a given point
 
 @param sphere_point
 @param ray_dir needs to evalute the normal direction: if inward (+) or outward (-) refered to the given ray direction
 */
Normal _sphere_normal(Point, Vec);

struct Shape;

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
  shared_ptr<Shape> shape;

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


//––––––––––––– Abstract struct Shapes ––––––––––––––––––––––––
//
/**
 * A generic 3D shape (sphere, plane...)
 *
 * It is an abstract stuct
 * with virtual methods ray_intersection(Ray) to be implemented in derived structs.
 */
struct Shape{

  Transformation transformation;
  Material material;

  Shape(Transformation t = Transformation(), Material m = Material()) : transformation{t}, material{m} {}

  virtual HitRecord ray_intersection(Ray) = 0;
  virtual bool check_if_intersection(Ray) = 0;
};


//––––––––––––– Sub-struct Sphere ––––––––––––––––––––––––
/**
 * A 3D unit sphere centered on the origin
 *
 * @param transformation changes properties of the unit sphere, through rescaling and translating it.
 */
struct Sphere : public Shape {

  Sphere(Transformation t = Transformation(), Material m = Material()) : Shape(t,m) {}
  
  //Se il vostro linguaggio lo supporta, il tipo di ritorno dovrebbe essere nullable.
  /**
   Checks if the given ray hits the sphere
   @param Ray Input ray to check
   @return HitRecord struct containing all infos about the ray-shape intersection (param 'init' set to faulse if no intersection happens)
   */
  HitRecord ray_intersection(Ray);
  
  /**
   Checks if the given ray hits the sphere
   @param ray Input ray to check
   @return boolean value
   */
  bool check_if_intersection(Ray);
  
};


//––––––––––––– Sub-struct Plane ––––––––––––––––––––––––
/**
 * A xy infinite plane
 *
 * @param transformation changes properties of the unit sphere, through translating and rotating it.
 */
struct Plane : public Shape {
  
  Plane(Transformation t = Transformation(), Material m = Material()) : Shape(t,m) {}
  
  /**
   Checks if the given ray hits the plane
   @param ray Input ray to check
   @return HitRecord struct containing all infos about the ray-shape intersection (param 'init' set to faulse if no intersection happens)
   */
  HitRecord ray_intersection(Ray);
  
  /**
   Checks if the given ray hits the sphere
   @param ray Input ray to check
   @return boolean value
   */
  bool check_if_intersection(Ray);
    
};


#endif
