#include "colors.h"
#include "geometry.h"
#include <cmath>
#include <iostream>
#include <sstream>

#ifndef _transformation_h_
#define _transformation_h_

//–––––––––––––––––––––– Struct Transformation –––––––––––––––––––––––––––––––––––

/*float IDENTITY_MATR4x4[4][4] = {{1.0, 0.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0, 0.0},
                                {0.0, 0.0, 1.0, 0.0},
                                {0.0, 0.0, 0.0, 1.0}};*/

bool are_matr_close(float [4][4], float [4][4]);

void matr_prod(const float m1[4][4], const float [4][4], float [4][4]);

struct Transformation {

  //float m[4][4] = IDENTITY_MATR4x4;  //error: array must be initialized with a brace-enclosed initializer
  //float invm[4][4] = IDENTITY_MATR4x4;

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

Transformation translation(Vec);

#endif
