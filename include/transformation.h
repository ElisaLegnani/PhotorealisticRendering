#include "functions.h"
#include "geometry.h"

#ifndef _transformation_h_
#define _transformation_h_

//–––––––––––––––––––––– Unit vectors i, j, k
//–––––––––––––––––––––––––––––––––––

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
