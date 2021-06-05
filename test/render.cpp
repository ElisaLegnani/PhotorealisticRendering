/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED “AS
IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "render.h"
#include "imagetracer.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("OnOffRenderer constructor", "[renderer]") {

  Sphere sphere(
      translation(Vec(2.0, 0.0, 0.0)) * scaling(Vec(0.2, 0.2, 0.2)),
      Material(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(WHITE))));
  HdrImage image(3, 3);
  OrthogonalCamera camera;
  ImageTracer tracer(image, make_shared<OrthogonalCamera>(camera));
  World world;
  world.add(make_shared<Sphere>(sphere));
  OnOffRenderer renderer(world);
  tracer.fire_all_rays(renderer);

  REQUIRE(tracer.image.get_pixel(0, 0).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 0).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(2, 0).is_close(BLACK));

  REQUIRE(tracer.image.get_pixel(0, 1).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 1).is_close(WHITE));
  REQUIRE(tracer.image.get_pixel(2, 1).is_close(BLACK));

  REQUIRE(tracer.image.get_pixel(0, 2).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 2).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(2, 2).is_close(BLACK));
}

TEST_CASE("FlatRenderer constructor", "[renderer]") {

  Color sphere_color(1.0, 2.0, 3.0);
  Sphere sphere(translation(Vec(2.0, 0.0, 0.0)) * scaling(Vec(0.2, 0.2, 0.2)),
                Material(make_shared<DiffuseBRDF>(make_shared<UniformPigment>(sphere_color))));
  HdrImage image(3, 3);
  OrthogonalCamera camera;
  ImageTracer tracer(image, make_shared<OrthogonalCamera>(camera));
  World world;
  world.add(make_shared<Sphere>(sphere));
  FlatRenderer renderer(world);
  tracer.fire_all_rays(renderer);

  REQUIRE(tracer.image.get_pixel(0, 0).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 0).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(2, 0).is_close(BLACK));

  REQUIRE(tracer.image.get_pixel(0, 1).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 1).is_close(sphere_color));
  REQUIRE(tracer.image.get_pixel(2, 1).is_close(BLACK));

  REQUIRE(tracer.image.get_pixel(0, 2).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(1, 2).is_close(BLACK));
  REQUIRE(tracer.image.get_pixel(2, 2).is_close(BLACK));
}