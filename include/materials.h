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

#include "hdrimage.h"
#include "pcg.h"
#include "ray.h"
#include <memory>

#ifndef _materials_h_
#define _materials_h_

//––––––––––––– Abstract struct Pigment ––––––––––––––––––––––––
/**
 * An abstract struct representing a pigment:
 * a function that associates a color with each point on a parametric surface (u,v)
 */
struct Pigment {
  /**
   * Pure virtual method to get the corrisponding color of the given 'Vec2d'
   */
  virtual Color get_color(Vec2d uv) = 0;
};

//––––––––––––– Sub-struct Uniform Pigment ––––––––––––––––––––––––
/**
 * A uniform pigment: a uniform color all over the surface
 *
 * @param color
 */
struct UniformPigment : public Pigment {

  Color color;

  UniformPigment(Color c) : color{c} {}

  Color get_color(Vec2d uv) { return color; }
};

//––––––––––––– Sub-struct Image Pigment ––––––––––––––––––––––––
/**
 * A pigment that textures the surface with a PFM image
 *
 * @param image PFM format
 */
struct ImagePigment : public Pigment {

  HdrImage image;

  ImagePigment(HdrImage i) : image{i} {}

  Color get_color(Vec2d uv);
};

//––––––––––––– Sub-struct Checkered Pigment ––––––––––––––––––––––––
/**
 * A pigment that textures the surface with a checkered pattern,
 * with tunable number of rows/colums
 *
 * @param color1
 * @param color2
 * @param n_steps integer indentifing the pattern alternation between colors (i.e. two colors repeats themselves every
 `n_steps` , dafault 10)
 */
struct CheckeredPigment : public Pigment {

  Color color1;
  Color color2;
  int n_steps;

  CheckeredPigment(Color c1, Color c2, int ns = 10)
      : color1{c1}, color2{c2}, n_steps{ns} {}

  Color get_color(Vec2d uv);
};

//––––––––––––– Abstract struct BRDF ––––––––––––––––––––––––
/** 
 * An abstract struct representing a Bidirectional Reflectance Distribution Function
 *
 * @param pigment
 */
struct BRDF {

  shared_ptr<Pigment> pigment;

  BRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(WHITE))
      : pigment{p} {}

  /**
   * Virtual method representing the specific BDRF equation.
   * Evaluate the color according to the surface features (diffusive, reflective...).
   *
   * Some parameters (i.e. directions) are needed to evalutes optics laws (e.g. riflection law):
   * @param normal of the surface in the surface hit point
   * @param dir_in inwards direction in the surface hit point
   * @param dir_out outwards direction in the surface hit point
   * @param uv 'Vec2d' corrisponding to the surface hit point
   *
   *             \               |               /
   *              \             |   n        /  dir_out
   *         dir_in     \           |           /
   *                \         |         /
   *                 \       |       /
   *                  \     |     /
   *                   \   |   /
   *                    \ | /
   * –––––––––––––––––––––––––– <-- uv ––––––––––––––––––––––––––––
   *
   *
   * @return Color
   */
  virtual Color eval(Normal n, Vec dir_in, Vec dir_out, Vec2d uv) = 0;

  /**
   * Virtual method to evaluate the outwards direction of the scattered (reflected or diffused) ray
   *
   * Some parameters are needed to evalute the outwards direction, others to create the 'Ray' struct:
   * @param pcg 'PCG' struct to evaluate the diffusion of the scattered ray
   * @param dir_in inwards direction
   * @param interaction_point surface hit point, starting point of the scattered ray
   * @param normal of the surface in the surface hit point
   * @param depth  integer parameter giving the number of reflections on surfaces
   *
   * @return 'Ray' with the outwards direction set
  */
  virtual Ray scatter_ray(PCG &pcg, Vec dir_in, Point interaction_point, Normal n, int depth) = 0;
  
  /**
   * Virtual method to print the type of BRDF (Diffusive or Specular).
   * It is useful for checking the code.
  */
  virtual void type() = 0;
};

//––––––––––––– Sub-struct Diffuse BRDF ––––––––––––––––––––––––
/** 
 * A struct representing an ideal diffuse BRDF
 *
 * @param reflectance
 */
struct DiffuseBRDF : public BRDF {

  float reflectance;

  DiffuseBRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(WHITE), float refl = 1.)
      : BRDF(p), reflectance{refl} {}

  Color eval(Normal n, Vec in_dir, Vec out_dir, Vec2d uv) {
    return pigment->get_color(uv) * (1. / M_PI);
  }

  Ray scatter_ray(PCG &pcg, Vec dir_in, Point interaction_point, Normal n, int depth);
  
  void type(){ cout << "DiffuseBRDF" << endl;}
};

//––––––––––––– Sub-struct Specular BRDF ––––––––––––––––––––––––
/** 
 * A struct representing an ideal mirror BRDF
 *
 * @param threshold_angle_rad
 */
struct SpecularBRDF : public BRDF {

  float threshold_angle_rad;

  SpecularBRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(WHITE), float ang = M_PI/180.0)
      : BRDF(p), threshold_angle_rad{ang} {}

  Color eval(Normal n, Vec in_dir, Vec out_dir, Vec2d uv);

  Ray scatter_ray(PCG &pcg, Vec dir_in, Point interaction_point, Normal n, int depth);
  
  void type(){ cout << "SpecularBRDF" << endl;}
};


//––––––––––––– Struct Material ––––––––––––––––––––––––
/**
 * A struct representing a material, which features are given by the two core terms of the rendering equation:
 *
 * @param brdf represents how the surface interacts with light rays
 * @param emitted_radiance represents light sources
 */

struct Material {

  shared_ptr<BRDF> brdf;
  shared_ptr<Pigment> emitted_radiance;

  Material(shared_ptr<BRDF> _brdf = make_shared<DiffuseBRDF>(),
           shared_ptr<Pigment> p = make_shared<UniformPigment>(BLACK))
      : brdf{_brdf}, emitted_radiance{p} {}
};

#endif
