#include "shapes.h"

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(HitRecord h1, HitRecord h2, string s="is_close()"){
  if (h1.is_close(h2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

void test_intersection(HitRecord intersection, string s="ray_intersection()"){
  if (intersection.init == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––

int main() {

  Sphere sphere;
  Ray ray1(Point(0.0, 0.0, 2.0), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  test_intersection(intersection1);
  test_closeness(intersection1, HitRecord(Point(0.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0), Vec2d(0.0, 0.0), 1.0, ray1));
  
  Ray ray2(Point(3, 0, 0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);

  test_intersection(intersection2);
  test_closeness(intersection2, HitRecord(Point(1.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0), Vec2d(0.0, 0.5), 2.0, ray2));
  

  Sphere sphere2(translation(Vec(10.0, 0.0, 0.0)));
  Ray ray3(Point(10, 0, 2), -VEC_Z);
  HitRecord intersection3 = sphere2.ray_intersection(ray3);

  test_intersection(intersection3);
  test_closeness(intersection3, HitRecord(Point(10.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0), Vec2d(0.0, 0.0), 1.0, ray3));  
  
  //finire!

  return 0;
}