#include "transformation.h"
#include <cmath>
#include <iostream>
#include <sstream>

//–––––––––––––––––––––– Unit vectors i, j, k –––––––––––––––––––––––––––––––––––

Vec VEC_X(1.0, 0.0, 0.0);
Vec VEC_Y(0.0, 1.0, 0.0);
Vec VEC_Z(0.0, 0.0, 1.0);

//–––––––––––––––––––––– Identity matrix –––––––––––––––––––––––––––––––––––

float IDENTITY_MATR4x4[4][4] = {{1.0, 0.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0, 0.0},
                                {0.0, 0.0, 1.0, 0.0},
                                {0.0, 0.0, 0.0, 1.0}};

//–––––––––––––––––––––– Functions for Struct Transformation –––––––––––––––––––––––––––––––––––

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

//–––––––––––––––––––––– Struct Transformation –––––––––––––––––––––––––––––––––––

Transformation::Transformation(float M[4][4], float invM[4][4]){
    for (int i{}; i<4; ++i){
      for (int j{}; j<4; ++j){
        m[i][j] = M[i][j];
        invm[i][j] = invM[i][j];
      }
    }
  };
  
  string Transformation::get_string() {
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

  bool Transformation::is_close(Transformation t){
    return are_matr_close(m, t.m) && are_matr_close(invm, t.invm);
  }

  bool Transformation::is_consistent(){
    float prod[4][4] = {};
    matr_prod(m, invm, prod);
    return are_matr_close(prod, IDENTITY_MATR4x4);
  }

  Transformation Transformation::inverse(){
    return Transformation{invm, m};
  }

//Transformation Transformation::translation(Vec){} //implementare

//implementare tutte le altre trasformazioni!

