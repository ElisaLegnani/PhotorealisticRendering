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

#include "world.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("World methods", "[world]"){
  
  World world;
 
  shared_ptr<Shape> sphere1 = make_shared<Sphere>(translation(VEC_X * 2));
  shared_ptr<Shape> sphere2 = make_shared<Sphere>(translation(VEC_X * 8));
  
  world.add(sphere1);
  world.add(sphere2);

  HitRecord intersection1 = world.ray_intersection(Ray(Point(0.0, 0.0, 0.0), VEC_X));
        
  REQUIRE(intersection1.init);
  REQUIRE(intersection1.world_point.is_close(Point(1.0, 0.0, 0.0)));

  HitRecord intersection2 = world.ray_intersection(Ray(Point(10.0, 0.0, 0.0), -VEC_X));

  REQUIRE(intersection2.init);
  REQUIRE(intersection2.world_point.is_close(Point(9.0, 0.0, 0.0)));

}
