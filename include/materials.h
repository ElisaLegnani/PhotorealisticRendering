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

#include "hdrimage.h"
#include "pcg.h"
#include "ray.h"
#include <memory>

#ifndef _materials_h_
#define _materials_h_

//––––––––––––– Abstract struct Pigment ––––––––––––––––––––––––
struct Pigment {
  virtual Color get_color(Vec2d uv) = 0;
};

//––––––––––––– Sub-struct Uniform Pigment ––––––––––––––––––––––––
struct UniformPigment : public Pigment {

  Color color;

  UniformPigment(Color c) : color{c} {}

  Color get_color(Vec2d uv) { return color; }
};

//––––––––––––– Sub-struct Image Pigment ––––––––––––––––––––––––
struct ImagePigment : public Pigment {

  HdrImage image;

  ImagePigment(HdrImage i) : image{i} {}

  Color get_color(Vec2d uv) {

    int col = int(uv.u * image.width);
    int row = int(uv.v * image.height);

    if (col >= image.width)
      col = image.width - 1;
    if (row >= image.height)
      row = image.height - 1;

    return image.get_pixel(col, row);
  }
};

//––––––––––––– Sub-struct Checkered Pigment ––––––––––––––––––––––––
struct CheckeredPigment : public Pigment {

  Color color1;
  Color color2;
  int n_steps;

  CheckeredPigment(Color c1, Color c2, int ns = 10)
      : color1{c1}, color2{c2}, n_steps{ns} {}

  Color get_color(Vec2d uv) {

    int u = int(floor(uv.u * n_steps));
    int v = int(floor(uv.v * n_steps));

    if ((u % 2) == (v % 2))
      return color1;
    else
      return color2;
  }
};

//––––––––––––– Abstract struct BRDF ––––––––––––––––––––––––
struct BRDF {

  shared_ptr<Pigment> pigment;

  BRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(WHITE))
      : pigment{p} {}

  Color eval(Normal n, Vec dir_in, Vec dir_out, Vec2d uv) { return BLACK; }

  virtual Ray scatter_ray(PCG pcg, Vec dir_in, Point interaction_point, Normal n, int depth) = 0;
};

//––––––––––––– Sub-struct Diffuse BRDF ––––––––––––––––––––––––

struct DiffuseBRDF : public BRDF {

  float reflectance;

  DiffuseBRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(WHITE), float refl = 1.)
      : BRDF(p), reflectance{refl} {}

  Color eval(Normal n, Vec in_dir, Vec out_dir, Vec2d uv) {
    return pigment->get_color(uv) * (reflectance / M_PI);
  }

  Ray scatter_ray(PCG pcg, Vec dir_in, Point interaction_point, Normal n, int depth){

    // Cosine-weighted distribution around the z (local) axis
    ONB onb(n);
    float cos_theta_sq = pcg.random_float();
    float cos_theta = sqrt(cos_theta_sq);
    float sin_theta = sqrt(1.0 - cos_theta_sq);
    float phi = 2.0 * M_PI * pcg.random_float();
    Vec dir(onb.e1 * cos(phi) * cos_theta + onb.e2 * sin(phi) * cos_theta + onb.e3 * sin_theta);

    return Ray(interaction_point, dir, 1.0e-3, INFINITY, depth);
  }
};

//––––––––––––– Struct Material ––––––––––––––––––––––––
struct Material {

  shared_ptr<BRDF> brdf;
  shared_ptr<Pigment> emitted_radiance;

  Material(shared_ptr<BRDF> _brdf = make_shared<DiffuseBRDF>(),
           shared_ptr<Pigment> p = make_shared<UniformPigment>(BLACK))
      : brdf{_brdf}, emitted_radiance{p} {}
};

#endif
