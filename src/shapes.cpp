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

#include "shapes.h"

//––––––––––––– Functions for Struct Sphere –––––––––––––––––––––––––

Vec2d sphere_point_to_uv(Point sp) {
  float u = atan2(sp.y, sp.x) / 2.0 / M_PI;
  float v = acos(sp.z) / M_PI;
  if (u >= 0.0) {
    return Vec2d(u, v);
  } else {
    return Vec2d((u + 1.0), v);
  }
}

Normal sphere_normal(Point sp, Vec ray_dir) {
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

  float t;
  if (tmin > inv_ray.tmin && tmin < inv_ray.tmax) {
    t = tmin;
  } else if (tmax > inv_ray.tmin && tmax < inv_ray.tmax) {
    t = tmax;
  } else {
    return HitRecord();
  }

  Point hit_point = inv_ray.at(t);

  return HitRecord((transformation * hit_point),
                   (transformation * sphere_normal(hit_point, inv_ray.dir)),
                   (sphere_point_to_uv(hit_point)), t, ray, material);
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
  
  float t = - inv_ray.origin.z / inv_ray.dir.z;

  if (t <= inv_ray.tmin || t >= inv_ray.tmax) return HitRecord();

  Point hit_point = inv_ray.at(t);

  float normal_z_dir=1.;
  if (inv_ray.dir.z > 0.0) normal_z_dir=-1.;
  
  return HitRecord((transformation * hit_point),
          transformation * Normal(0.0, 0.0, normal_z_dir),
          Vec2d(hit_point.x - floor(hit_point.x), hit_point.y - floor(hit_point.y)), t, ray, material);
}

bool Plane::check_if_intersection(Ray ray){
    
  Ray inv_ray(ray.transform(transformation.inverse()));
  
  if (fabs(inv_ray.dir.z)< 1e-5) return false;
  
  double t = - inv_ray.origin.z / inv_ray.dir.z;

  return (t > inv_ray.tmin && t < inv_ray.tmax);
}

//––––––––––––– Sub-struct Box ––––––––––––––––––––––––

/* box faces
        _______
 ______|_back__|________________
|_left_|__top__|_right_|_bottom_|
       |_front_|
        _____
  _____|__4__|___________
 |__0__|__5__|__3__|__2__|
       |__1__|
*/

HitRecord Box::ray_intersection(Ray ray) {

  Ray inv_ray(ray.transform(transformation.inverse()));

  float t1, t2;
  float tmin = inv_ray.tmin;
  float tmax = inv_ray.tmax;
  int facemin, facemax;

  for (int i{}; i < 3; ++i) {

    t1 = (Pmin[i] - inv_ray.origin[i]) / inv_ray.dir[i];
    t2 = (Pmax[i] - inv_ray.origin[i]) / inv_ray.dir[i];

    if (t1 < t2) {
      
      if (t1 > tmin) {
        tmin = t1;
        facemin = i;
      }
      if (t2 < tmax) {
        tmax = t2;
        facemax = i + 3;
      }

    } else {

      if (t2 > tmin) {
        tmin = t2;
        facemin = i + 3;
      }
      if (t1 < tmax) {
        tmax = t1;
        facemax = i;
      }
    }
    
    if (tmin > tmax) return HitRecord();
  }

  float t;
  int face;
  if (tmin > inv_ray.tmin && tmin < inv_ray.tmax) {
    t = tmin;
    face = facemin;
  } else if (tmax > inv_ray.tmin && tmax < inv_ray.tmax) {
    t = tmax;
    face = facemax;
  } else {
    return HitRecord();
  }

  Normal normal = box_normal(face, inv_ray.dir);
  Point hit_point = inv_ray.at(t);
  
  return HitRecord(transformation * hit_point,
          transformation * normal,
          box_point_to_uv(hit_point, face), t, ray, material);
}

bool Box::check_if_intersection(Ray ray) {
  
  Ray inv_ray(ray.transform(transformation.inverse()));

  float t1, t2;
  float tmin = inv_ray.tmin;
  float tmax = inv_ray.tmax;
  int facemin, facemax;

  for (int i{}; i < 3; ++i) {

    t1 = (Pmin[i] - inv_ray.origin[i]) / inv_ray.dir[i];
    t2 = (Pmax[i] - inv_ray.origin[i]) / inv_ray.dir[i];

    if (t1 < t2) {
      
      if (t1 > tmin) {
        tmin = t1;
        facemin = i;
      }
      if (t2 < tmax) {
        tmax = t2;
        facemax = i + 3;
      }

    } else {

      if (t2 > tmin) {
        tmin = t2;
        facemin = i + 3;
      }
      if (t1 < tmax) {
        tmax = t1;
        facemax = i;
      }
    }
    
    if (tmin > tmax) return false;
  }

  return ((tmin > inv_ray.tmin && tmin < inv_ray.tmax) || (tmax > inv_ray.tmin && tmax < inv_ray.tmax));
}

Vec2d Box::box_point_to_uv(Point hit_point, int face) {

  float u, v;

  if (face == 0 || face == 3) {
    u = (face + (hit_point.y - Pmin.y) / (Pmax.y - Pmin.y)) / 6.0;
    v = (face + (hit_point.z - Pmin.z) / (Pmax.z - Pmin.z)) / 6.0;
  } else if (face == 1 || face == 4) {
    u = (face + (hit_point.x - Pmin.x) / (Pmax.x - Pmin.x)) / 6.0;
    v = (face + (hit_point.z - Pmin.z) / (Pmax.z - Pmin.z)) / 6.0;
  } else if (face == 2 || face == 5) {
    u = (face + (hit_point.x - Pmin.x) / (Pmax.x - Pmin.x)) / 6.0;
    v = (face + (hit_point.y - Pmin.y) / (Pmax.y - Pmin.y)) / 6.0;
  }

  return Vec2d(u, v);
}


Normal Box::box_normal(int face, Vec ray_dir) {

  Normal normal;
  if (face == 0 || face == 3)
    normal = Normal(1, 0, 0);
  else if (face == 1 || face == 4)
    normal = Normal(0, 1, 0);
  else if (face == 2 || face == 5)
    normal = Normal(0, 0, 1);

  if (dot(ray_dir, normal) < 0)
    return normal;
  else
    return -normal;
}
