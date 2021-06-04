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
