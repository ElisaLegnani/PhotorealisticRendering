#include "hitrecord.h"
#include "shapes.h"
#include <vector>
#include <memory>

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

  vector<shared_ptr<Shape>> shapes;

    /**
   * Add a new shape to the world
   */
  void add(shared_ptr<Shape> s){
    shapes.push_back(s);
  }

  /**
   * Check whether a light ray intersects any of the shapes in the world 
   */
  HitRecord ray_intersection(Ray ray){
    HitRecord closest;
    for(int i{}; i<shapes.size(); ++i){
      HitRecord intersection = shapes[i]->ray_intersection(ray);
      if(intersection.init){
        if(!closest.init || intersection.t < closest.t){
          closest = intersection;
        }
      }
    } 
    return closest;
  }    
};

#endif
