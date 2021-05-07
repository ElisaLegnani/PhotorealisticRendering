#include "transformation.h"
#include "ray.h"

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(Ray r1, Ray r2, string s="is_close()"){
  if (r1.is_close(r2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    cout << "Origin1: "; r1.origin.get_string();
    cout << "Dir1:"; r1.dir.get_string();
    abort();
  }
}

void test_not_closeness(Ray r1, Ray r2, string s="is_close()"){
  if (r1.is_close(r2) != 0) {
    cout << "Error: "<<s<<"." << endl;
    cout << "Origin1: "; r1.origin.get_string();
    cout << "Dir1:"; r1.dir.get_string();
    abort();
  }
}

void test_closeness(Point p1, Point p2, string s="is_close()"){
  if (p1.is_close(p2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

void test_closeness(Vec v1, Vec v2, string s="is_close()"){
  if (v1.is_close(v2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––

int main() {
  
  Ray ray1(Point(1.0, 2.0, 3.0), Vec(5.0, 4.0, -1.0));
  Ray ray2(Point(1.0, 2.0, 3.0), Vec(5.0, 4.0, -1.0));
  Ray ray3(Point(5.0, 1.0, 4.0), Vec(3.0, 9.0, 4.0));

  test_closeness(ray1, ray2);
  test_not_closeness(ray1,ray3);
  
//  Test at

  Ray ray4(Point(1.0, 2.0, 4.0), Vec(4.0, 2.0, 1.0));
  test_closeness(ray4.at(0.0),ray4.origin, "at()");
  test_closeness(ray4.at(1.0),Point(5.0, 4.0, 5.0), "at()");
  test_closeness(ray4.at(2.0),Point(9.0, 6.0, 6.0), "at()");

  //  Test transform
  
  Ray ray5(Point(1.0, 2.0, 3.0), Vec(6.0, 5.0, 4.0));
  
  Transformation tr=translation(Vec(10.0, 11.0, 12.0))* rotation_x(90.0);
  
  Ray transformed=ray5.transform(tr);
  
  test_closeness(transformed.origin,Point(11.0, 8.0, 14.0), "transform() on origin");
  test_closeness(transformed.dir,Vec(6.0, -4.0, 5.0), "transform() on direction");

return 0;
}
