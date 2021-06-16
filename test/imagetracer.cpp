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

#include "imagetracer.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

// Setup
HdrImage image(4, 2);
shared_ptr<Camera> camera = make_shared<PerspectiveCamera>(1.0, 2.0);
ImageTracer tracer(image, camera);

// Test orientation
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
