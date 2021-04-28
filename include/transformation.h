#include "colors.h"
#include "geometry.h"
#include <cmath>
#include <iostream>
#include <sstream>

#ifndef _transformation_h_
#define _transformation_h_

//–––––––––––––––––––––– Struct Transformation –––––––––––––––––––––––––––––––––––

float IDENTITY_MATR4x4[4][4] = {{1.0, 0.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0, 0.0},
                                {0.0, 0.0, 1.0, 0.0},
                                {0.0, 0.0, 0.0, 1.0}};

bool are_matr_close(float m1[4][4], float m2[4][4]){
  for (int i{}; i<4; ++i){
    for (int j{}; j<4; ++j){
      if(!(are_close(m1[i][j], m2[i][j]))) return false;
    }
  }
  return true;
}

void matr_prod(const float m1[4][4], const float m2[4][4], float m[4][4]){
  for (int i{}; i<4; ++i){
    for (int j{}; j<4; ++j){
      for (int k{}; k<4; ++k){
        m[i][j] += m1[i][k] * m[k][j];
      }  
    }
  }
}

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

  Transformation(float M[4][4], float invM[4][4]){
    for (int i{}; i<4; ++i){
      for (int j{}; j<4; ++j){
        m[i][j] = M[i][j];
        invm[i][j] = invM[i][j];
      }
    }
  };
  
  string print_string() {
    ostringstream stream;
    stream << "Transformation \n";
    for (int i{}; i<4; ++i){
      for (int j{}; j<4; ++j){
        stream << m[i][j] << " ";
      }
      stream << "\n";
    }
    return stream.str();
  }

  bool is_close(Transformation t){
    return are_matr_close(m, t.m) && are_matr_close(invm, t.invm);
  }

  bool is_consistent(){
    float prod[4][4] = {};
    matr_prod(m, invm, prod);
    return are_matr_close(prod, IDENTITY_MATR4x4);
  }

  Transformation inverse(){
    return Transformation{invm, m};
  }

};

Transformation translation(Vec); //implementare

//implementare tutte le altre trasformazioni!


#endif
