#include "geometry.h"
#include "transformation.h"
#include "ray.h"
#include "hitrecord.h"

#ifndef _shapes_h_
#define _shapes_h_

Vec2d _sphere_point_to_uv(Point);
Normal _sphere_normal(Point, Vec);

/**
 * A generic 3D shape (sphere, plane...)
 *
 * It is an abstract stuct
 * with virtual methods ray_intersection(Ray) to be implemented in derived structs.
 */
struct Shape{
  virtual HitRecord ray_intersection(Ray) = 0;
  virtual bool check_if_intersection(Ray) = 0;
};

//Se il vostro linguaggio lo supporta, il tipo di ritorno dovrebbe essere nullable.
/**
 * A 3D unit sphere centered on the origin
 *
 * @param transformation changes properties of the unit sphere, through rescaling and translating it.
 */
struct Sphere : public Shape {
  
  Transformation transformation;
  // Material material;

  Sphere(Transformation t = Transformation()) : transformation{t} {} // da aggiungere material come trasnformation
  
  /**
   Checks if the given ray hits the sphere
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

/**
 * A xy infinite plane
 *
 * @param transformation changes properties of the unit sphere, through translating and rotating it.
 */

struct Plane : public Shape {
  Transformation transformation;
  
  Plane(Transformation t = Transformation()) : transformation{t} {}
  
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
