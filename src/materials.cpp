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
