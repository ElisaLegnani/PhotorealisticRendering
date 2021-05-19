#include "imagetracer.h"

//–––––––––– Functions supporting tests –––––––––––––––

void test_closeness(Point p1, Point p2, string s="is_close()"){
  if (p1.is_close(p2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

void test_closeness(Ray r1, Ray r2, string s="is_close()"){
  if (r1.is_close(r2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}

void test_closeness(Color c1, Color c2, string s="is_close()"){
  if (c1.is_color_close(c2) == 0) {
    cout << "Error: "<< s <<"." << endl;
    abort();
  }
}


int main() {

  //Setup
  HdrImage image(4, 2);
  shared_ptr<Camera> camera = make_shared<PerspectiveCamera>(1.0, 2.0);
  ImageTracer tracer(image, camera);

  // Test orientation

  Ray top_left_ray = tracer.fire_ray(0, 0, 0.0, 0.0);
  test_closeness(Point(0.0, 2.0, 1.0), top_left_ray.at(1.0), "Wrong orientation");

  // Test uv sub-mapping
  // Here we're cheating: we are asking `ImageTracer.fire_ray` to fire one ray *outside* the pixel we're specifying

  Ray ray1 = tracer.fire_ray(0, 0, 2.5, 1.5);
  Ray ray2 = tracer.fire_ray(2, 1, 0.5, 0.5);
  test_closeness(ray1, ray2, "uv sub-mapping");

  // Test image coverage

  tracer.fire_all_rays([](Ray ray) -> Color{ return Color(1.0, 2.0, 3.0);} );

  for (int row{}; row < tracer.image.height; ++row) {
    for (int col{}; col < tracer.image.width; ++col) {
      test_closeness(tracer.image.get_pixel(col, row), Color(1.0, 2.0, 3.0), "Image coverage");
    }
  }

  return 0;
}
