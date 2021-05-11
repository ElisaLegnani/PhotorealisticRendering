#include "geometry.h"
#include "transformation.h"
#include "ray.h"

// tutto in sospesssooooo
// https://stackoverflow.com/questions/7425241/how-to-return-null-object-in-c

#ifndef _shapes_h_
#define _shapes_h_

struct Shapes{
  virtual HitRecord ray_intersection(Ray) = 0;
};

//Se il vostro linguaggio lo supporta, il tipo di ritorno dovrebbe essere nullable.
struct Sphere : public Shapes {
  
  Transformation transformation;

  Sphere(Transformation t = Transformation()) : transformation{t} {}
  
  HitRecord ray_intersection(Ray ray){
    Ray inv_ray(ray.transform(transformation.inverse()));
    Vec origin_vec(inv_ray.origin.to_vec());
    float a=inv_ray.dir.squared_norm();
    float b=2.0 * origin_vec.dot(inv_ray.dir);
    float c=origin_vec.squared_norm() - 1.0;
    
    delta = b * b - 4.0 * a * c;
    
  }
  
};

struct Plane : public Shapes {
  
};


#endif
