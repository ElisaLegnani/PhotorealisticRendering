#include "transformation.h"
#include <cmath>
#include <iostream>
#include <sstream>

//–––––––––––––––––––––– Unit vectors i, j, k
//–––––––––––––––––––––––––––––––––––

Vec VEC_X(1.0, 0.0, 0.0);
Vec VEC_Y(0.0, 1.0, 0.0);
Vec VEC_Z(0.0, 0.0, 1.0);

//–––––––––––––––––––––– Identity matrix –––––––––––––––––––––––––––––––––––

float IDENTITY_MATR4x4[4][4] = {{1.0, 0.0, 0.0, 0.0},
                                {0.0, 1.0, 0.0, 0.0},
                                {0.0, 0.0, 1.0, 0.0},
                                {0.0, 0.0, 0.0, 1.0}};

//–––––––––––––––––––––– Functions for Struct Transformation
//–––––––––––––––––––––––––––––––––––

bool are_matr_close(float m1[4][4], float m2[4][4]) {
  for (int i{}; i < 4; ++i) {
    for (int j{}; j < 4; ++j) {
      if (!(are_close(m1[i][j], m2[i][j])))
        return false;
    }
  }
  return true;
}

void matr_prod(const float m1[4][4], const float m2[4][4], float m3[4][4]) {
  for (int i{}; i < 4; ++i) {
    for (int j{}; j < 4; ++j) {
      for (int k{}; k < 4; ++k) {
        m3[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
}

//–––––––––––––––––––––– Struct Transformation
//–––––––––––––––––––––––––––––––––––

Transformation::Transformation(float M[4][4], float invM[4][4]) {
  for (int i{}; i < 4; ++i) {
    for (int j{}; j < 4; ++j) {
      m[i][j] = M[i][j];
      invm[i][j] = invM[i][j];
    }
  }
};

string Transformation::get_string() {
  ostringstream stream;
  stream << "Transformation \n";
  for (int i{}; i < 4; ++i) {
    for (int j{}; j < 4; ++j) {
      stream << m[i][j] << " ";
    }
    stream << "\n";
  }
  return stream.str();
}

bool Transformation::is_close(Transformation t) {
  return are_matr_close(m, t.m) && are_matr_close(invm, t.invm);
}

bool Transformation::is_consistent() {
  float prod[4][4] = {};
  matr_prod(m, invm, prod);
  return are_matr_close(prod, IDENTITY_MATR4x4);
}

Transformation Transformation::inverse() { return Transformation{invm, m}; }

Transformation operator*(Transformation t1, Transformation t2){
  float m_prod[4][4] = {};
  float invm_prod[4][4] = {};
  matr_prod(t1.m, t2.m, m_prod);
  matr_prod(t2.invm, t1.invm, invm_prod); // Reverse order (A B)^-1 = B^-1 A^-1
  return Transformation(m_prod, invm_prod);
}

Point operator*(Transformation t, Point p){
  Point newp(p.x * t.m[0][0] + p.y * t.m[0][1] + p.z * t.m[0][2] + t.m[0][3],
            p.x * t.m[1][0] + p.y * t.m[1][1] + p.z * t.m[1][2] + t.m[1][3],
            p.x * t.m[2][0] + p.y * t.m[2][1] + p.z * t.m[2][2] + t.m[2][3]);
  
  float w = p.x * t.m[3][0] + p.y * t.m[3][1] + p.z * t.m[3][2] + t.m[3][3];

  if (w == 1.0) return newp;
  else return Point(newp.x / w, newp.y / w, newp.z / w);
}

Vec operator*(Transformation t, Vec v){
  return Vec(v.x * t.m[0][0] + v.y * t.m[0][1] + v.z * t.m[0][2],
              v.x * t.m[1][0] + v.y * t.m[1][1] + v.z * t.m[1][2],
              v.x * t.m[2][0] + v.y * t.m[2][1] + v.z * t.m[2][2]);
}

Normal operator*(Transformation t, Normal n){ // n'=(M-1)^t * n
  return Normal(n.x * t.invm[0][0] + n.y * t.invm[1][0] + n.z * t.invm[2][0],
                n.x * t.invm[0][1] + n.y * t.invm[1][1] + n.z * t.invm[2][1],
                n.x * t.invm[0][2] + n.y * t.invm[1][2] + n.z * t.invm[2][2]);
}

Transformation translation(Vec v){

  float mt[4][4]={{1.0, 0.0, 0.0, v.x},
                  {0.0, 1.0, 0.0, v.y},
                  {0.0, 0.0, 1.0, v.z},
                  {0.0, 0.0, 0.0, 1.0}};

  float invmt[4][4]={{1.0, 0.0, 0.0, -v.x},
                    {0.0, 1.0, 0.0, -v.y},
                    {0.0, 0.0, 1.0, -v.z},
                    {0.0, 0.0, 0.0, 1.0}};

  return Transformation(mt, invmt);
}

Transformation scaling(Vec v){

  float ms[4][4]={{v.x, 0.0, 0.0, 0.0},
                  {0.0, v.y, 0.0, 0.0},
                  {0.0, 0.0, v.z, 0.0},
                  {0.0, 0.0, 0.0, 1.0}};

  float invms[4][4]={{1/v.x, 0.0, 0.0, 0.0},
                    {0.0, 1/v.y, 0.0, 0.0},
                    {0.0, 0.0, 1/v.z, 0.0},
                    {0.0, 0.0, 0.0, 1.0}};

  return Transformation(ms, invms);
}

Transformation rotation_x(float theta_rad){ //verifica in rad (es <lim_sup)?

  float sinT=sin(theta_rad);
  float cosT=cos(theta_rad);
  
  float mrx[4][4]={{1.0, 0.0, 0.0, 0.0},
                  {0.0, cosT, -sinT, 0.0},
                  {0.0, sinT, cosT, 0.0},
                  {0.0, 0.0, 0.0, 1.0}};

  float invmrx[4][4]={{1.0, 0.0, 0.0, 0.0},
                    {0.0, cosT, sinT, 0.0},
                    {0.0, -sinT, cosT, 0.0},
                    {0.0, 0.0, 0.0, 1.0}};

  return Transformation(mrx, invmrx);
}

Transformation rotation_y(float theta_rad){

  float sinT=sin(theta_rad);
  float cosT=cos(theta_rad);
  
  float mry[4][4]={{cosT, 0.0, sinT, 0.0},
                  {0.0, 1.0, 0.0, 0.0},
                  {-sinT, 0.0, cosT, 0.0},
                  {0.0, 0.0, 0.0, 1.0}};

  float invmry[4][4]={{cosT, 0.0, -sinT, 0.0},
                    {0.0, 1.0, 0.0, 0.0},
                    {sinT, 0.0, cosT, 0.0},
                    {0.0, 0.0, 0.0, 1.0}};

  return Transformation(mry, invmry);
}

Transformation rotation_z(float theta_rad){

  float sinT=sin(theta_rad);
  float cosT=cos(theta_rad);
  
  float mrz[4][4]={{cosT, -sinT, 0.0, 0.0},
                  {sinT, cosT, 0.0, 0.0},
                  {0.0, 0.0, 1.0, 0.0},
                  {0.0, 0.0, 0.0, 1.0}};

  float invmrz[4][4]={{cosT, sinT, 0.0, 0.0},
                    {-sinT, cosT, 0.0, 0.0},
                    {0.0, 0.0, 1.0, 0.0},
                    {0.0, 0.0, 0.0, 1.0}};

  return Transformation(mrz, invmrz);
}
