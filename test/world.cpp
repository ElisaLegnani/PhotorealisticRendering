#include "world.h"

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(Point p1, Point p2, string s="is_close()"){
  if (p1.is_close(p2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}


//––––––––––––––––––––––––––––––––––––––––––––––––––––––––

int main() {
  
  World world;
  
  Sphere sphere1(translation(VEC_X * 2));
  Sphere sphere2(translation(VEC_X * 8));
  
  world.add(sphere1);
  world.add(sphere2);

  HitRecord intersection1 = world.ray_intersection(Ray(Point(0.0, 0.0, 0.0), VEC_X));
        
  //test_intersection(intersection1);
  test_closeness(intersection1.world_point, Point(1.0, 0.0, 0.0));

  HitRecord intersection2 = world.ray_intersection(Ray(Point(10.0, 0.0, 0.0), -VEC_X));

  //test_intersection(intersection2);
  test_closeness(intersection2.world_point,Point(9.0, 0.0, 0.0));

  return 0;
}
