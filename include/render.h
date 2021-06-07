#include "colors.h"
#include "ray.h"
#include "world.h"
#include "materials.h"

#ifndef _render_h_
#define _render_h_

struct Renderer {

  World world;
  Color background_color;

  Renderer(World w, Color bc = BLACK): world{w}, background_color{bc} {}

  virtual Color operator()(Ray ray) = 0;
};


/**
 A renderer with
 - ON mode (default: white)
 - OFF mode (default: black)
 Used mainly for debugging porpuses
 */
struct OnOffRenderer : public Renderer{
  Color color;
  
  OnOffRenderer(World w, Color bc = BLACK, Color c = WHITE): Renderer(w,bc), color{c} {}
  
  Color operator()(Ray ray){
    if(world.ray_intersection(ray).init){
      return color;
    }else{
      return background_color;
    }
  }
  
};


struct FlatRenderer : public Renderer{
  
  FlatRenderer(World w, Color bc = BLACK): Renderer(w,bc) {}
  
  Color operator()(Ray ray){
    
    HitRecord hit = world.ray_intersection(ray);
    
    if (!hit.init){
      
      return background_color;
  
    }else{
      
      return (hit.material.brdf->pigment->get_color(hit.surface_point) +
              hit.material.emitted_radiance->get_color(hit.surface_point));
    }
  }
};

#endif

