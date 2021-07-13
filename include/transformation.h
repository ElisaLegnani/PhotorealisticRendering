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
 * Rescale of an ammount given by a 'Vec'
 *
 * @param v 'Vec' object specifing the amount of scaling along the three directions X, Y, Z.
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
