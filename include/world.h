#include "hitrecord.h"
#include "ray.h"
#include "shapes.h"

#ifndef _world_h_
#define _world_h_

/**
 * A struct containing a list of shapes that make up the "world"
 *
 * Shapes can be added to a world using the method `add`
 * The method `ray_intersection` can be used to check whether a light ray
 * intersects any of the shapes in the world
 */
struct World {

  vector<Shape> shapes;

  World(){};

  /**
   * Add a new shape to the world
   */
  void add(Shape s){
  }
  
};