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

//–––––––––––––––––––––– Functions for Transformation –––––––––––––––––––––––––––––––––––

bool are_matr_close(float [4][4], float [4][4]);

void matr_prod(const float [4][4], const float [4][4], float [4][4]);


//–––––––––––––––––––––– Struct Transformation –––––––––––––––––––––––––––––––––––
/**
 * A struct reprenting an affine transformation.
 * It is the output when calling a 'translation', 'scaling' or 'rotation' function.
 *
 * @param m transformation matrix
 * @param invm inverse transformation matrix, implemented to increase the code efficiency
 */
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
  
  /**
   * Return a printable strings showing the transformation matrix content
   */
  string get_string();

  /**
   * Check if the transformation can be considered the same as the given one
   * Needed to avoid floating-point approximation limits.
   */
  bool is_close(Transformation);
  
  /**
   * Check if the transformation is consistent ( m X invm = identity_matrix )
   */
  bool is_consistent();

  /**
   * Retrun the inverse transformation ( i.e. swap 'm' and 'invm' )
   */
  Transformation inverse();

};

//–––––––––––––– Operations –––––––––––––––
Transformation operator*(Transformation, Transformation);
Point operator*(Transformation, Point);
Vec operator*(Transformation, Vec);
Normal operator*(Transformation, Normal);

//–––––––––––––– Transformations –––––––––––––––
/**
 * Translate of a given 'Vec' oriented in 3D space
 *
 * @param v 'Vec' object generating the translation
 * @return 'Transformation' object representing the translation
 */
Transformation translation(Vec);

/**
 * Rescale of a given 'Vec'
 *
 * @param v 'Vec' object generating the scaling
 * @return 'Transformation' object representing the scaling
 */
Transformation scaling(Vec);

/**
 * Rotate around x-axis of a given angle
 *
 * @param angle_deg floating-point number reprensenting the angle in degrees
 * @return 'Transformation' object representing the x-rotation
 */
Transformation rotation_x(float);

/**
 * Rotate around y-axis of a given angle
 *
 * @param angle_deg floating-point number reprensenting the angle in degrees
 * @return 'Transformation' object representing the y-rotation
 */
Transformation rotation_y(float);

/**
 * Rotate around z-axis of a given angle
 *
 * @param angle_deg floating-point number reprensenting the angle in degrees
 * @return 'Transformation' object representing the z-rotation
 */
Transformation rotation_z(float);

#endif
