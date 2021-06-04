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
