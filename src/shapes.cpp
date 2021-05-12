#include "shapes.h"
#include <cmath>
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

  if (delta <= 0.0) {
    return HitRecord();
  }

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
