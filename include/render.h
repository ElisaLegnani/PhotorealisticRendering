#include "colors.h"
#include "ray.h"
#include "world.h"

#ifndef _render_h_
#define _render_h_

struct Renderer {

  World world;
  Color background_color;

  Renderer(World w, Color bc = BLACK): world{w}, background_color{bc} {}

  virtual Color call(Ray r) = 0;
};

#endif

