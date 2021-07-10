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

#include "materials.h"

//––––––––––––– Sub-struct Image Pigment ––––––––––––––––––––––––
Color ImagePigment :: get_color(Vec2d uv) {

  int col = int(uv.u * image.width);
  int row = int(uv.v * image.height);

  if (col >= image.width)
    col = image.width - 1;
  if (row >= image.height)
    row = image.height - 1;

  return image.get_pixel(col, row);
}

//––––––––––––– Sub-struct Checkered Pigment ––––––––––––––––––––––––
Color CheckeredPigment :: get_color(Vec2d uv) {

  int u = int(floor(uv.u * n_steps));
  int v = int(floor(uv.v * n_steps));

  if ((u % 2) == (v % 2))
    return color1;
  else
    return color2;
}

//––––––––––––– Sub-struct Diffuse BRDF ––––––––––––––––––––––––
Ray DiffuseBRDF :: scatter_ray(PCG &pcg, Vec dir_in, Point interaction_point, Normal n, int depth){

  // Cosine-weighted distribution around the z (local) axis
  ONB onb(n);
  float cos_theta_sq = pcg.random_float();
  float cos_theta = sqrt(cos_theta_sq);
  float sin_theta = sqrt(1.0 - cos_theta_sq);
  float phi = 2.0 * M_PI * pcg.random_float();
  Vec dir(onb.e1 * cos(phi) * cos_theta + onb.e2 * sin(phi) * cos_theta + onb.e3 * sin_theta);

  return Ray(interaction_point, dir, 1.0e-3, INFINITY, depth);
}

//––––––––––––– Sub-struct Specular BRDF ––––––––––––––––––––––––
Color SpecularBRDF :: eval(Normal n, Vec in_dir, Vec out_dir, Vec2d uv) {
  float theta_in = acos(normalized_dot(in_dir, n));
  float theta_out = acos(normalized_dot(out_dir, n));

  if (fabs(theta_in - theta_out) < threshold_angle_rad)
    return pigment->get_color(uv);
  else
    return BLACK;

}

Ray SpecularBRDF :: scatter_ray(PCG &pcg, Vec dir_in, Point interaction_point, Normal n, int depth) {
  // There is no need to use the PCG here, as the reflected direction is always completely deterministic 
  // for a perfect mirror
  Vec ray_dir(dir_in.x, dir_in.y, dir_in.z);
  ray_dir.normalize();
  n.normalize();
  float dot_prod = dot(ray_dir, n);

  return Ray(interaction_point, (ray_dir - n * 2 * dot_prod), 1e-5, INFINITY, depth);
}
