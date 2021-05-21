#include "geometry.h"
#include "transformation.h"
#include "ray.h"
#include "hitrecord.h"

#ifndef _shapes_h_
#define _shapes_h_

Vec2d _sphere_point_to_uv(Point);
Normal _sphere_normal(Point, Vec);

struct Shape{
  virtual HitRecord ray_intersection(Ray) = 0;
};

//Se il vostro linguaggio lo supporta, il tipo di ritorno dovrebbe essere nullable.
struct Sphere : public Shape {
  
  Transformation transformation;

  Sphere(Transformation t = Transformation()) : transformation{t} {}
  
  HitRecord ray_intersection(Ray);
  
};

/*struct Plane : public Shape {
  
};*/


#endif
