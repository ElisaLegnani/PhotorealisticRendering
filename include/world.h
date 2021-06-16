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
