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

#include "shapes.h"
#include "lights.h"
#include <vector>
#include <memory>

#ifndef _world_h_
#define _world_h_

/**
 * A struct containing a list of shapes & lights that make up the "world"
 *
 * Shapes can be added to a world using the method `add_shape`
 * Lights can be added to a world using the method `add_light`
 * The method `ray_intersection` can be used to check whether a light ray intersects any of the shapes in the world
 */
struct World {

  vector<shared_ptr<Shape>> shapes;
  vector<PointLight> lights;

  /**
   * Add a new shape to the world
   */
  void add_shape(shared_ptr<Shape> s){
    shapes.push_back(s);
  }
  
/**
 * Add a new light to the world
 */
void add_light(PointLight l){
  lights.push_back(l);
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
          closest.normal.normalize();
        }
      }
    } 
    return closest;
  }
  
  /**
   * Check whether a point is visible form an observer point of view (pov), with no shape in the middle
   */
  bool is_point_visible (Point point, Point observer_pov){
    Vec dir = point - observer_pov;
    float dir_norm = dir.norm();
    
    Ray ray(observer_pov, dir, 1e-2/dir_norm, 1., 0);
    
    for(int s{}; s < shapes.size(); ++s){
      if(shapes[s]->check_if_intersection(ray)) return false;
    }
    return true;
  }
};

#endif
