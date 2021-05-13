#include "imagetracer.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

HdrImage image(4, 2);
PerspectiveCamera camera(1.0, 2.0);
ImageTracer tracer(image, camera);

TEST_CASE("ImageTracer orientation", "[imagetracer]") {

  Ray top_left_ray = tracer.fire_ray(0, 0, 0.0, 0.0);

  REQUIRE(top_left_ray.at(1.0).is_close(Point(0.0, 2.0, 1.0)));
}

// Test uv sub-mapping
// Here we're cheating: we are asking `ImageTracer.fire_ray` to fire one ray *outside* the pixel we're specifying
TEST_CASE("ImageTracer uv sub-mapping", "[imagetracer]") {

  Ray ray1 = tracer.fire_ray(0, 0, 2.5, 1.5);
  Ray ray2 = tracer.fire_ray(2, 1, 0.5, 0.5);

  REQUIRE(ray1.is_close(ray2));
}

TEST_CASE("ImageTracer image coverage", "[imagetracer]") {

  tracer.fire_all_rays([](Ray ray) -> Color { return Color(1.0, 2.0, 3.0); });

  for (int row{}; row < tracer.image.height; ++row) {
    for (int col{}; col < tracer.image.width; ++col) {
      REQUIRE(tracer.image.get_pixel(col, row).is_close(Color(1.0, 2.0, 3.0)));
    }
  }
}
