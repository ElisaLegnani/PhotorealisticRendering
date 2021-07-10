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

#include "geometry.h"
#include "materials.h"
#include "ray.h"
#include "transformation.h"
#include <string>

#ifndef _shapes_h_
#define _shapes_h_

//––––––––––––– Functions for sub-Struct Sphere ––––––––––––––––––

/**
 * Convert a 3D sphere point to 2D (u,v) surface coordinates
 */
Vec2d sphere_point_to_uv(Point);

/**
 * Evaluate the normal of the sphere in a given point of its surface,
 * which is always in the opposite direction with respect to
 * the direction of the ray hitting the sphere
 *
 * @param sphere_point A point on the sphere's surface
 * @param ray_dir The ray's direction
 */
Normal sphere_normal(Point, Vec);

struct Shape;

//––––––––––––– Struct HitRecord –––––––––––––––––––––––––
/**
 * A struct containing information about a ray & shape intersection
 *
 * @param ray The ray that hits the shape surface
 * @param world_point The 3D coordinates in the space where the ray hits the shape
 * @param normal The normal of the shape in the point of the ray-shape intersection
 * @param surface_point The 2D (u,v) coordinates of the hit point on the shape surface
 * @param t The distance between the origin of the ray and the hit point
 * @param material The shape's material
 */
struct HitRecord {

  Ray ray;
  Point world_point;
  Normal normal;
  Vec2d surface_point;
  float t;
  Material material;
  bool init = false;

  HitRecord() { init = false; }

  HitRecord(Point wp, Normal n, Vec2d sp, float T, Ray r, Material m = Material())
      : world_point(wp), normal(n), surface_point(sp), t(T), ray(r), material{m} {
    init = true;
  }

  bool is_close(HitRecord hitrec) {
    return world_point.is_close(hitrec.world_point) &&
           normal.is_close(hitrec.normal) &&
           surface_point.is_close(hitrec.surface_point) &&
           are_close(t, hitrec.t) && ray.is_close(hitrec.ray);
  }
};

//––––––––––––– Abstract struct Shapes ––––––––––––––––––––––––
/**
 * A generic 3D shape (sphere, plane, box)
 *
 * It is an abstract stuct
 * with virtual methods ray_intersection(Ray) and check_if_intersection(Ray)
 * to be implemented in derived structs
 *
 * @param transformation The transformation to apply to the shape
 * @param material The material of the shape
 */
struct Shape {

  Transformation transformation;
  Material material;

  Shape(Transformation t = Transformation(), Material m = Material())
      : transformation{t}, material{m} {}

  virtual HitRecord ray_intersection(Ray) = 0;
  virtual bool check_if_intersection(Ray) = 0;
};

//––––––––––––– Sub-struct Sphere ––––––––––––––––––––––––
/**
 * A 3D unit sphere centered on the origin
 *
 * @param transformation The transformation to apply to the unit sphere
 * @param material The material of the sphere
 */
struct Sphere : public Shape {

  Sphere(Transformation t = Transformation(), Material m = Material())
      : Shape(t, m) {}

  /**
   * Check if the given ray hits the sphere
   *
   * @param Ray Input ray to check
   * @return HitRecord struct containing all infos about the ray-sphere intersection 
   * (param 'init' set to false if no intersection happens)
   */
  HitRecord ray_intersection(Ray);

  /**
   * Check if the given ray hits the sphere or not
   *
   * @param ray Input ray to check
   * @return boolean value
   */
  bool check_if_intersection(Ray);
};

//––––––––––––– Sub-struct Plane ––––––––––––––––––––––––
/**
 * A xy infinite plane
 *
 * @param transformation The transformation to apply to the plane
 * @param material The material of the plane
 */
struct Plane : public Shape {

  Plane(Transformation t = Transformation(), Material m = Material())
      : Shape(t, m) {}

  /**
   * Check if the given ray hits the plane
   *
   * @param ray Input ray to check
   * @return HitRecord struct containing all infos about the ray-plane intersection
   * (param 'init' set to false if no intersection happens)
   */
  HitRecord ray_intersection(Ray);

  /**
   * Check if the given ray hits the plane or not
   *
   * @param ray Input ray to check
   * @return boolean value
   */
  bool check_if_intersection(Ray);
};

//––––––––––––– Sub-struct Box ––––––––––––––––––––––––
/**
 * An axis-aligned box (AAB)
 *
 * @param transformation The transformation to apply to the box
 * @param material The material of the box
 * @param Pmin A vertex of the box
 * @param Pmax The opposite vertex
 *
 */
struct Box : public Shape {

  Point Pmin, Pmax;

  Box(Point pmin = Point(0, 0, 0), Point pmax = Point(1, 1, 1),
      Transformation t = Transformation(), Material m = Material())
      : Shape(t, m), Pmin{pmin}, Pmax{pmax} {}

  /**
   * Check if the given ray hits the box
   *
   * @param ray Input ray to check
   * @return HitRecord struct containing all infos about the ray-box intersection
   * (param 'init' set to false if no intersection happens)
   */
  HitRecord ray_intersection(Ray);

  /**
   * Check if the given ray hits the box or not
   *
   * @param ray Input ray to check
   * @return boolean value
   */
  bool check_if_intersection(Ray);

  /**
   * Convert a 3D box point to 2D (u,v) coordinates on one face of the box
   */
  Vec2d box_point_to_uv(Point, int);

  /**
   * Evaluate the normal of the box in a given point of its surface,
   * which is always in the opposite direction with respect to
   * the direction of the ray hitting the box
   *
   * @param face One of the faces of the box, represented by an integer in [1,6]
   * @param ray_dir The ray's direction
   */
  Normal box_normal(int, Vec);
};

#endif
