#include "colors.h"
#include "materials.h"
#include "ray.h"
#include "world.h"

#ifndef _render_h_
#define _render_h_

struct Renderer {

  World world;
  Color background_color;

  Renderer(World w, Color bc = BLACK) : world{w}, background_color{bc} {}

  virtual Color operator()(Ray ray) = 0;
};

/**
 A renderer with
 - ON mode (default: white)
 - OFF mode (default: black)
 Used mainly for debugging porpuses
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

    Color cum_radiance;
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

#endif
