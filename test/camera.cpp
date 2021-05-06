#include "camera.h"

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

  //–––––––– Test OrthogonalCamera ––––––––

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
  test_closeness(ray2.at(1.0), Point(0.0, -2.0, -1.0), "OrthogonalCamera, wrong hitting coordinates");
  test_closeness(ray3.at(1.0), Point(0.0, 2.0, 1.0), "OrthogonalCamera, wrong hitting coordinates");
  test_closeness(ray4.at(1.0), Point(0.0, -2.0, 1.0), "OrthogonalCamera, wrong hitting coordinates");


  //Test transform
  Transformation tr = translation(-1*Vec(0.0, 1.0, 0.0) * 2.0) * rotation_z(M_PI/2.0); //risolvere VEC_Y & -vec & rotation(rad-deg) !
  OrthogonalCamera cam2(1.0, tr);
  Ray ray = cam2.fire_ray(0.5, 0.5);
  test_closeness(ray.at(1.0), Point(0.0, -2.0, 0.0), "OrthogonalCamera, transform");


  //–––––––– Test PerspectiveCamera –––––––– 

  PerspectiveCamera cam3(1.0, 2.0);

  // Fire one ray for each corner of the image plane
  Ray ray5 = cam3.fire_ray(0.0, 0.0);
  Ray ray6 = cam3.fire_ray(1.0, 0.0);
  Ray ray7 = cam3.fire_ray(0.0, 1.0);
  Ray ray8 = cam3.fire_ray(1.0, 1.0);

  // Verify that all the rays depart from the same point
  test_closeness(ray5.origin, ray6.origin, "PerspectiveCamera, rays do not depart from the same point");
  test_closeness(ray5.origin, ray7.origin, "PerspectiveCamera, rays do not depart from the same point");
  test_closeness(ray5.origin, ray8.origin, "PerspectiveCamera, rays do not depart from the same point");

  // Verify that the ray hitting the corners have the right coordinates
  test_closeness(ray5.at(1.0), Point(0.0, 2.0, -1.0), "PerspectiveCamera, wrong hitting coordinates");
  test_closeness(ray6.at(1.0), Point(0.0, -2.0, -1.0), "PerspectiveCamera, wrong hitting coordinates");
  test_closeness(ray7.at(1.0), Point(0.0, 2.0, 1.0), "PerspectiveCamera, wrong hitting coordinates");
  test_closeness(ray8.at(1.0), Point(0.0, -2.0, 1.0), "PerspectiveCamera, wrong hitting coordinates");


  // Test transform
  Transformation tr2 = translation(-1*Vec(0.0, 1.0, 0.0) * 2.0) * rotation_z(M_PI/2.0); //risolvere VEC_Y & -vec & rotation(rad-deg) !
  OrthogonalCamera cam4(1.0, tr2);
  Ray ray9 = cam4.fire_ray(0.5, 0.5);
  test_closeness(ray9.at(1.0), Point(0.0, -2.0, 0.0), "OrthogonalCamera, transform");
  
  return 0;
}