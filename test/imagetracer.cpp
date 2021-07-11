/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

TEST_CASE("ImageTracer antialiasing", "[imagetracer]") {

  int n_rays = 0;
  HdrImage small_image(1, 1);
  shared_ptr<Camera> camera = make_shared<OrthogonalCamera>(1.0);
  ImageTracer tracer(small_image, camera, 10, PCG());

  tracer.fire_all_rays([&n_rays](Ray ray) -> Color { 
    Point point = ray.at(1);

    // Check that all the rays intersect the screen within the region [−1, 1] × [−1, 1]
    REQUIRE(are_close(point.x, 0.0));
    REQUIRE(-1.0 <= point.y);
    REQUIRE(point.y <= 1.0);
    REQUIRE(-1.0 <= point.z);
    REQUIRE(point.z <= 1.0);

    n_rays += 1;

    return BLACK;
  });

  REQUIRE(n_rays == 100);
}