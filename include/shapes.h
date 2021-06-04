#include "geometry.h"
#include "transformation.h"
#include "ray.h"
#include "hitrecord.h"

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


//––––––––––––– Abstract struct Shapes ––––––––––––––––––––––––
//
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


//––––––––––––– Sub-struct Sphere ––––––––––––––––––––––––
/**
 * A 3D unit sphere centered on the origin
 *
 * @param transformation changes properties of the unit sphere, through rescaling and translating it.
 */
struct Sphere : public Shape {
  
  Transformation transformation;
  // Material material;

  Sphere(Transformation t = Transformation()) : transformation{t} {} // da aggiungere material come trasnformation
  
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
