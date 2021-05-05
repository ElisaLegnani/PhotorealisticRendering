#include "camera.h"
//#include <cstdlib>

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(float a, float b, string s="is_close()"){
  if (are_close(a, b) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

void test_closeness(Point p1, Point p2, string s="is_close()"){
  if (p1.is_close(p2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}


int main() {

  // Test OrthogonalCamera

  OrthogonalCamera cam(2.0);

  // Fire one ray for each corner of the image plane

  Ray ray1 = cam.fire_ray(0.0, 0.0);
  Ray ray2 = cam.fire_ray(1.0, 0.0);
  Ray ray3 = cam.fire_ray(0.0, 1.0);
  Ray ray4 = cam.fire_ray(1.0, 1.0);

  // Verify that the rays are parallel by verifying that cross-products vanish

  test_closeness(0.0, cross(ray1.dir, ray2.dir).squared_norm(), "OrthogonalCamera, rays not parallel");
  test_closeness(0.0, cross(ray1.dir, ray3.dir).squared_norm(), "OrthogonalCamera, rays not parallel");
  test_closeness(0.0, cross(ray1.dir, ray4.dir).squared_norm(), "OrthogonalCamera, rays not parallel");

  // Verify that the ray hitting the corners have the right coordinates

  test_closeness(ray1.at(1.0), Point(0.0, 2.0, -1.0), "OrthogonalCamera, wrong hitting coordinates");
  test_closeness(ray1.at(1.0), Point(0.0, -2.0, -1.0), "OrthogonalCamera, wrong hitting coordinates");
  test_closeness(ray1.at(1.0), Point(0.0, 2.0, 1.0), "OrthogonalCamera, wrong hitting coordinates");
  test_closeness(ray1.at(1.0), Point(0.0, -2.0, 1.0), "OrthogonalCamera, wrong hitting coordinates");
  
  return 0;
}