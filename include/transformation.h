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

#include "functions.h"
#include "geometry.h"

#ifndef _transformation_h_
#define _transformation_h_

//––––––––––––––––––––– Unit vectors i, j, k ––––––––––––––––––––––––––––––––––

#define VEC_X Vec(1.0, 0.0, 0.0)
#define VEC_Y Vec(0.0, 1.0, 0.0)
#define VEC_Z Vec(0.0, 0.0, 1.0)

//–––––––––––––––––––––– Struct Transformation –––––––––––––––––––––––––––––––––––

bool are_matr_close(float [4][4], float [4][4]);

void matr_prod(const float [4][4], const float [4][4], float [4][4]);


struct Transformation {

  float m[4][4] = {{1.0, 0.0, 0.0, 0.0},
                   {0.0, 1.0, 0.0, 0.0},
                   {0.0, 0.0, 1.0, 0.0},
                   {0.0, 0.0, 0.0, 1.0}};

  float invm[4][4] = {{1.0, 0.0, 0.0, 0.0},
                      {0.0, 1.0, 0.0, 0.0},
                      {0.0, 0.0, 1.0, 0.0},
                      {0.0, 0.0, 0.0, 1.0}};

  Transformation(){};

  Transformation(float [4][4], float [4][4]);
  
  string get_string();

  bool is_close(Transformation);
  
  bool is_consistent();

  Transformation inverse();

};

//–––––––––––––– Operations –––––––––––––––
Transformation operator*(Transformation, Transformation);
Point operator*(Transformation, Point);
Vec operator*(Transformation, Vec);
Normal operator*(Transformation, Normal);

//–––––––––––––– Transformations –––––––––––––––
Transformation translation(Vec);
Transformation scaling(Vec);
Transformation rotation_x(float);
Transformation rotation_y(float);
Transformation rotation_z(float);

#endif
