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

#include "colors.h"
#include "materials.h"
#include "ray.h"
#include "world.h"

#ifndef _render_h_
#define _render_h_

//––––––––––––– Abstract struct Render ––––––––––––––––––––––––
/**
 * An abstract struct implementing a solver of the rendering equation
 *
 * @param world
 * @param background_color
 */
struct Renderer {

  World world;
  Color background_color;

  Renderer(World w, Color bc = BLACK) : world{w}, background_color{bc} {}

  /** Estimates the radiance along a ray */
  virtual Color operator()(Ray ray) = 0;
};

//––––––––––––– Sub-struct OnOffRender ––––––––––––––––––––––––
/**
 * A renderer with
 * - ON mode (default: white)
 * - OFF mode (default: black)
 * Used mainly for debugging purposes
 *
 * @param color of the world's shapes hit by a ray
 */
struct OnOffRenderer : public Renderer {
  Color color;

  OnOffRenderer(World w, Color bc = BLACK, Color c = WHITE)
      : Renderer(w, bc), color{c} {}

  Color operator()(Ray ray) {
    if (world.ray_intersection(ray).init) {
      return color;
    } else {
      return background_color;
    }
  }
};

//––––––––––––– Sub-struct FlatRender ––––––––––––––––––––––––
/**
 * A flat renderer:
 * it estimates the solution of the rendering equation neglecting any contribution of the light
 * it uses the pigment of each surface to compute the final radiance
 */
struct FlatRenderer : public Renderer {

  FlatRenderer(World w, Color bc = BLACK) : Renderer(w, bc) {}

  Color operator()(Ray ray) {

    HitRecord hit = world.ray_intersection(ray);

    if (!hit.init) {

      return background_color;

    } else {

      return (hit.material.brdf->pigment->get_color(hit.surface_point) +
              hit.material.emitted_radiance->get_color(hit.surface_point));
    }
  }
};

//––––––––––––– Sub-struct PathTracer ––––––––––––––––––––––––
/**
 * A path-tracing renderer
 *
 * @param pcg
 * @param num_of_rays number of rays thrown at each iteration
 * @param max_depth maximum depth of the rays
 * @param russian_roulette_limit allows the algorithm to complete the calculation
 even if max_depth is set to infinity, using the Roussian roulette method
 */
struct PathTracer : public Renderer {

  PCG pcg;
  int num_of_rays;
  int max_depth;
  int russian_roulette_limit;

  PathTracer(World w, Color bc = BLACK, PCG pcg = PCG(), int nrays = 10, int maxd = 2, int rrlim = 3)
      : Renderer(w, bc), num_of_rays{nrays}, max_depth{maxd}, russian_roulette_limit{rrlim} {}

  Color operator()(Ray ray) {
    
    if (ray.depth > max_depth)
      return BLACK;
      
    HitRecord hit = world.ray_intersection(ray);

    if (!hit.init)
      return background_color;

    Material hit_material = hit.material;
    Color hit_color = hit_material.brdf->pigment->get_color(hit.surface_point);
    Color emitted_radiance = hit_material.emitted_radiance->get_color(hit.surface_point);

    float hit_color_lum = fmax(fmax(hit_color.r, hit_color.g), hit_color.b);

    // Russian roulette
    if (ray.depth >= russian_roulette_limit){
      if (pcg.random_float() > hit_color_lum)  
        hit_color = hit_color * ( 1.0 / (1.0 - hit_color_lum));
        // Keep the recursion going, but compensate for other potentially discarded rays
      else
        return emitted_radiance;
        // Terminate prematurely
    }

    Color cum_radiance(BLACK);
    if (hit_color_lum > 0.0){  // Only do costly recursions if it's worth it
      for (int i{}; i < num_of_rays; ++i){
        Ray new_ray = hit_material.brdf->scatter_ray(pcg, hit.ray.dir, hit.world_point, hit.normal, (ray.depth + 1));
        // Recursive call
        Color new_radiance = (*this)(new_ray);
        cum_radiance = cum_radiance + hit_color * new_radiance;
      }
    }

    return emitted_radiance + cum_radiance * (1.0 / num_of_rays);
  }
};
//––––––––––––– Sub-struct PointLightTracer ––––––––––––––––––––––––
struct PointLightTracer : public Renderer {
};
//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

#endif
