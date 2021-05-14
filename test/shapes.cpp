#include "shapes.h"

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(HitRecord h1, HitRecord h2,
                    string s = "HitRecord: is_close()") {
  if (h1.is_close(h2) == 0) {
    cout << "Error: " << s << "." << endl;
    abort();
  }
}

void test_closeness(Normal n1, Normal n2, string s = "Normal: is_close()") {
  if (n1.is_close(n2) == 0) {
    cout << "Error: " << s << "." << endl;
    abort();
  }
}

void test_closeness(Vec2d v1, Vec2d v2, string s = "Vec2d: is_close()") {
  if (v1.is_close(v2) == 0) {
    cout << "Error: " << s << "." << endl;
    abort();
  }
}

void test_intersection(HitRecord intersection,
                       string s = "ray_intersection()") {
  if (intersection.init == 0) {
    cout << "Error: " << s << "." << endl;
    abort();
  }
}

void test_not_intersection(HitRecord intersection,
                           string s = "ray_intersection()") {
  if (intersection.init != 0) {
    cout << "Error: " << s << "." << endl;
    abort();
  }
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––

int main() {

  // Test hit

  Sphere sphere;
  Ray ray1(Point(0.0, 0.0, 2.0), -VEC_Z);
  HitRecord intersection1 = sphere.ray_intersection(ray1);

  test_intersection(intersection1);
  test_closeness(intersection1,
                 HitRecord(Point(0.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0),
                           Vec2d(0.0, 0.0), 1.0, ray1));

  Ray ray2(Point(3, 0, 0), -VEC_X);
  HitRecord intersection2 = sphere.ray_intersection(ray2);

  test_intersection(intersection2);
  test_closeness(intersection2,
                 HitRecord(Point(1.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0),
                           Vec2d(0.0, 0.5), 2.0, ray2));

  test_not_intersection(sphere.ray_intersection(Ray(Point(0, 10, 2), -VEC_Z)));

  // Test internal hit

  Ray ray3(Point(0, 0, 0), VEC_X);
  HitRecord intersection3 = sphere.ray_intersection(ray3);

  test_intersection(intersection3);
  test_closeness(intersection3,
                 HitRecord(Point(1.0, 0.0, 0.0), Normal(-1.0, 0.0, 0.0),
                           Vec2d(0.0, 0.5), 1.0, ray3));

  // Test transformation

  Sphere sphere2(translation(Vec(10.0, 0.0, 0.0)));
  Ray ray4(Point(10, 0, 2), -VEC_Z);
  HitRecord intersection4 = sphere2.ray_intersection(ray4);

  test_intersection(intersection4);
  test_closeness(intersection4,
                 HitRecord(Point(10.0, 0.0, 1.0), Normal(0.0, 0.0, 1.0),
                           Vec2d(0.0, 0.0), 1.0, ray4));

  Ray ray5(Point(13, 0, 0), -VEC_X);
  HitRecord intersection5 = sphere2.ray_intersection(ray5);

  test_intersection(intersection5);
  test_closeness(intersection5,
                 HitRecord(Point(11.0, 0.0, 0.0), Normal(1.0, 0.0, 0.0),
                           Vec2d(0.0, 0.0), 2.0, ray5));

  // Check if the sphere failed to move by trying to hit the untransformed shape
  test_not_intersection(sphere2.ray_intersection(Ray(Point(0, 0, 2), -VEC_Z)));

  // Check if the *inverse* transformation was wrongly applied
  test_not_intersection(
      sphere2.ray_intersection(Ray(Point(-10, 0, 0), -VEC_Z)));

  // Test normals

  Sphere sphere3(scaling(Vec(2.0, 1.0, 1.0)));
  Ray ray6(Point(1.0, 1.0, 0.0), Vec(-1.0, -1.0));
  HitRecord intersection6 = sphere3.ray_intersection(ray6);

  // We normalize "intersection.normal", as we are not interested in its length
  test_closeness(intersection6.normal.normalize(),
                 Normal(1.0, 4.0, 0.0).normalize());

  // Test normal direction

  // Scaling a sphere by -1 keeps the sphere the same but reverses its reference frame
  Sphere sphere4(scaling(Vec(-1.0, -1.0, -1.0)));

  Ray ray7(Point(0.0, 2.0, 0.0), -VEC_Y);
  HitRecord intersection7 = sphere4.ray_intersection(ray7);

  test_closeness(intersection7.normal.normalize(),
                 Normal(0.0, 1.0, 0.0).normalize());

  // Test uv coordinates

  Sphere sphere5;

  Ray ray8(Point(2.0, 0.0, 0.0), -VEC_X);
  test_closeness(sphere5.ray_intersection(ray8).surface_point, Vec2d(0.0, 0.5));

  Ray ray9(Point(0.0, 2.0, 0.0), -VEC_Y);
  test_closeness(sphere5.ray_intersection(ray9).surface_point,
                 Vec2d(0.25, 0.5));

  Ray ray10(Point(-2.0, 0.0, 0.0), VEC_X);
  test_closeness(sphere5.ray_intersection(ray10).surface_point,
                 Vec2d(0.5, 0.5));

  Ray ray11(Point(0.0, -2.0, 0.0), -VEC_Y);
  test_closeness(sphere5.ray_intersection(ray11).surface_point,
                 Vec2d(0.75, 0.5));

  Ray ray12(Point(2.0, 0.0, 0.5), -VEC_X);
  test_closeness(sphere5.ray_intersection(ray12).surface_point,
                 Vec2d(0.0, 1 / 3));

  Ray ray13(Point(2.0, 0.0, -0.5), -VEC_X);
  test_closeness(sphere5.ray_intersection(ray13).surface_point,
                 Vec2d(0.0, 2 / 3));

  return 0;
}