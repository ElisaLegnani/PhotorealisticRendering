#include "shapes.h"

//––––––––––––– Functions for Struct Sphere –––––––––––––––––––––––––

Vec2d _sphere_point_to_uv(Point sp) {
  float u = atan2(sp.y, sp.x) / 2.0 / M_PI;
  float v = acos(sp.z) / M_PI;
  if (u >= 0.0) {
    return Vec2d(u, v);
  } else {
    return Vec2d((u + 1.0), v);
  }
}

Normal _sphere_normal(Point sp, Vec ray_dir) {
  Normal normal = Normal(sp.x, sp.y, sp.z);
  if (dot(sp.to_vec(), ray_dir) < 0.0) {
    return normal;
  } else {
    return (-normal);
  }
}

//––––––––––––– Sub-struct Sphere ––––––––––––––––––––––––

HitRecord Sphere::ray_intersection(Ray ray) {

  Ray inv_ray(ray.transform(transformation.inverse()));
  Vec origin_vec(inv_ray.origin.to_vec());
  float a = inv_ray.dir.squared_norm();
  float b = 2.0 * dot(origin_vec, inv_ray.dir);
  float c = origin_vec.squared_norm() - 1.0;

  float delta = b * b - 4.0 * a * c;

  if (delta <= 0.0) return HitRecord();

  float tmin = (-b - sqrt(delta)) / 2.0 / a;
  float tmax = (-b + sqrt(delta)) / 2.0 / a;

  float first_hit_t;
  if (tmin > inv_ray.tmin && tmin < inv_ray.tmax) {
    first_hit_t = tmin;
  } else if (tmax > inv_ray.tmin && tmax < inv_ray.tmax) {
    first_hit_t = tmax;
  } else {
    return HitRecord();
  }

  Point hit_point = inv_ray.at(first_hit_t);

  return HitRecord((transformation * hit_point),
                   (transformation * _sphere_normal(hit_point, inv_ray.dir)),
                   (_sphere_point_to_uv(hit_point)), first_hit_t, ray);
}

bool Sphere::check_if_intersection(Ray ray){
  
  Ray inv_ray(ray.transform(transformation.inverse()));
  Vec origin_vec(inv_ray.origin.to_vec());
  float a = inv_ray.dir.squared_norm();
  float b = 2.0 * dot(origin_vec, inv_ray.dir);
  float c = origin_vec.squared_norm() - 1.0;

  float delta = b * b - 4.0 * a * c;

  if (delta <= 0.0) return false;

  float tmin = (-b - sqrt(delta)) / 2.0 / a;
  float tmax = (-b + sqrt(delta)) / 2.0 / a;
  
  return ((tmin > inv_ray.tmin && tmin < inv_ray.tmax) || (tmax > inv_ray.tmin && tmax < inv_ray.tmax));
}

//––––––––––––– Sub-struct Plane ––––––––––––––––––––––––

HitRecord Plane::ray_intersection(Ray ray){
  Ray inv_ray(ray.transform(transformation.inverse()));
  
  if (fabs(inv_ray.dir.z)< 1e-5){ //i.e. parallel to xy plane
    return HitRecord();
  }
  
  double t = - inv_ray.origin.z / inv_ray.dir.z;

  if (t <= inv_ray.tmin || t >= inv_ray.tmax) return HitRecord();

  Point hit_point = inv_ray.at(t);

  float normal_z_dir=1.;
  if (inv_ray.dir.z > 0.0) normal_z_dir=-1.;
  
       return HitRecord((transformation * hit_point),
           transformation * Normal(0.0, 0.0, normal_z_dir),
          Vec2d(hit_point.x - floor(hit_point.x), hit_point.y - floor(hit_point.y)), t, ray);
}

bool Plane::check_if_intersection(Ray ray){
    
  Ray inv_ray(ray.transform(transformation.inverse()));
  
  if (fabs(inv_ray.dir.z)< 1e-5) return false;
  
  double t = - inv_ray.origin.z / inv_ray.dir.z;

  return (t >inv_ray.tmin && t< inv_ray.tmax);
}
