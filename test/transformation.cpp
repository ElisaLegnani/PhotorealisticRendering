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

#include "transformation.h"
#include "catch_amalgamated.hpp"

#define CATCH_CONFIG_MAIN

// test get_string da fare ?

float m[4][4] = {{1.0, 2.0, 3.0, 4.0},
                 {5.0, 6.0, 7.0, 8.0},
                 {9.0, 9.0, 8.0, 7.0},
                 {6.0, 5.0, 4.0, 1.0}};

float invm[4][4] = {{-3.75, 2.75, -1, 0},
                    {4.375, -3.875, 2.0, -0.5},
                    {0.5, 0.5, -1.0, 1.0},
                    {-1.375, 0.875, 0.0, -0.5}};

Transformation t(m, invm);

TEST_CASE("Transformation consistency", "[transformation]") {
  REQUIRE(t.is_consistent());
}

TEST_CASE("Transformation is_close", "[transformation]") {

  Transformation t2(m, invm);
  Transformation t3(m, invm);
  t3.m[2][2] += 1.0;
  Transformation t4(m, invm);
  t4.invm[2][2] += 1.0;

  REQUIRE(t.is_close(t2));
  REQUIRE(!t.is_close(t3));
  REQUIRE(!t.is_close(t4));
}

TEST_CASE("Transformation operator* (Transformation*Transformation)",
          "[transformation]") {

  float m2[4][4] = {{3.0, 5.0, 2.0, 4.0},
                    {4.0, 1.0, 0.0, 5.0},
                    {6.0, 3.0, 2.0, 0.0},
                    {1.0, 4.0, 2.0, 1.0}};

  float invm2[4][4] = {{0.4, -0.2, 0.2, -0.6},
                       {2.9, -1.7, 0.2, -3.1},
                       {-5.55, 3.15, -0.4, 6.45},
                       {-0.9, 0.7, -0.2, 1.1}};

  Transformation t2(m2, invm2);
  REQUIRE(t2.is_consistent());

  float m3[4][4] = {{33.0, 32.0, 16.0, 18.0},
                    {89.0, 84.0, 40.0, 58.0},
                    {118.0, 106.0, 48.0, 88.0},
                    {63.0, 51.0, 22.0, 50.0}};

  float invm3[4][4] = {{-1.45, 1.45, -1.0, 0.6},
                       {-13.95, 11.95, -6.5, 2.6},
                       {25.525, -22.025, 12.25, -5.2},
                       {4.825, -4.325, 2.5, -1.1}};

  Transformation t3(m3, invm3);
  REQUIRE(t3.is_consistent());

  REQUIRE(t3.is_close(t * t2));
}

TEST_CASE("Transformation operator*", "[transformation]") {

  float m2[4][4] = {{1.0, 2.0, 3.0, 4.0},
                    {5.0, 6.0, 7.0, 8.0},
                    {9.0, 9.0, 8.0, 7.0},
                    {0.0, 0.0, 0.0, 1.0}};

  float invm2[4][4] = {{-3.75, 2.75, -1, 0},
                       {5.75, -4.75, 2.0, 1.0},
                       {-2.25, 2.25, -1.0, -2.0},
                       {0.0, 0.0, 0.0, 1.0}};

  Transformation t2(m2, invm2);
  REQUIRE(t2.is_consistent());

  Vec v(14.0, 38.0, 51.0);
  REQUIRE(v.is_close(t2 * Vec(1.0, 2.0, 3.0)));

  Point p(18.0, 46.0, 58.0);
  REQUIRE(p.is_close(t2 * Point(1.0, 2.0, 3.0)));

  Normal n(-8.75, 7.75, -3.0);
  REQUIRE(n.is_close(t2 * Normal(3.0, 2.0, 4.0)));
}

TEST_CASE("Transformation inverse", "[transformation]") {

  Transformation t2 = t.inverse();
  REQUIRE(t2.is_consistent());

  Transformation prod = t * t2;
  REQUIRE(prod.is_consistent());

  REQUIRE(!prod.is_close(t));
}

TEST_CASE("Transformation translation", "[transformation]") {

  Transformation tr1 = translation(Vec(1.0, 2.0, 3.0));
  REQUIRE(tr1.is_consistent());

  Transformation tr2 = translation(Vec(4.0, 6.0, 8.0));
  REQUIRE(tr2.is_consistent());

  Transformation prod = tr1 * tr2;
  REQUIRE(prod.is_consistent());

  Transformation tr3 = translation(Vec(5.0, 8.0, 11.0));
  REQUIRE(prod.is_close(tr3));
}

TEST_CASE("Transformation scaling", "[transformation]") {

  Transformation sc1 = scaling(Vec(2.0, 5.0, 10.0));
  REQUIRE(sc1.is_consistent());

  Transformation sc2 = scaling(Vec(3.0, 2.0, 4.0));
  REQUIRE(sc2.is_consistent());

  Transformation sc3 = scaling(Vec(6.0, 10.0, 40.0));
  Transformation prod3 = sc1 * sc2;

  REQUIRE(prod3.is_close(sc3));
}

TEST_CASE("Transformation rotations", "[transformation]") {

  Transformation rx1 = rotation_x(0.1);
  Transformation ry1 = rotation_y(0.1);
  Transformation rz1 = rotation_z(0.1);

  REQUIRE(rx1.is_consistent());
  REQUIRE(ry1.is_consistent());
  REQUIRE(rz1.is_consistent());

  Transformation rx2 = rotation_x(90.0);
  Transformation ry2 = rotation_y(90.0);
  Transformation rz2 = rotation_z(90.0);

  REQUIRE((rx2 * VEC_Y).is_close(VEC_Z));
  REQUIRE((ry2 * VEC_Z).is_close(VEC_X));
  REQUIRE((rz2 * VEC_X).is_close(VEC_Y));
}
