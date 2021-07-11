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

#include "world.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("World methods", "[world]"){
  
  World world;
 
  shared_ptr<Shape> sphere1 = make_shared<Sphere>(translation(VEC_X * 2));
  shared_ptr<Shape> sphere2 = make_shared<Sphere>(translation(VEC_X * 8));
  
  world.add_shape(sphere1);
  world.add_shape(sphere2);

  HitRecord intersection1 = world.ray_intersection(Ray(Point(0.0, 0.0, 0.0), VEC_X));
        
  REQUIRE(intersection1.init);
  REQUIRE(intersection1.world_point.is_close(Point(1.0, 0.0, 0.0)));

  HitRecord intersection2 = world.ray_intersection(Ray(Point(10.0, 0.0, 0.0), -VEC_X));

  REQUIRE(intersection2.init);
  REQUIRE(intersection2.world_point.is_close(Point(9.0, 0.0, 0.0)));
  
//  check_if_intersection and is_point_visible
  REQUIRE(!world.is_point_visible(Point(10.0, 0.0, 0.0), Point(0.0, 0.0, 0.0)));
  REQUIRE(!world.is_point_visible(Point(5.0, 0.0, 0.0), Point(0.0, 0.0, 0.0)));
  REQUIRE(world.is_point_visible(Point(5.0, 0.0, 0.0), Point(4.0, 0.0, 0.0)));
  REQUIRE(world.is_point_visible(Point(0.5, 0.0, 0.0), Point(0.0, 0.0, 0.0)));
  REQUIRE(world.is_point_visible(Point(0.0, 10.0, 0.0), Point(0.0, 0.0, 0.0)));
  REQUIRE(world.is_point_visible(Point(0.0, 0.0, 10.0), Point(0.0, 0.0, 0.0)));

}
