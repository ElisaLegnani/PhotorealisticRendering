#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

#ifndef _geometry_h_
#define _geometry_h_

template <typename In1, typename In2, typename Out>
Out _sum(const In1 &a, const In2 &b) {
  return Out{a.x + b.x, a.y + b.y, a.z + b.z};
}

bool are_close(float x, float y) {
  float epsilon = 1e-10;
  return abs(x - y) < epsilon;
}

/*bool are_xyz_close(Vec v1, Vec v2) {
  return are_close(v1.x, v2.x) && are_close(v1.y, v2.y) && are_close(v1.z, v2.z);
}*/

struct Vec{
  float x, y, z;
      
      Vec(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
      Vec(const Vec &); // Copy constructor
      Vec(const Vec &&); // Move constructor
  
  Vec operator+(const Vec &a, const Vec &b) {
    return _sum<Vec, Vec, Vec>(a, b);
  }
  
  bool is_close(Vec v) {
    return are_close(x, v.x) && are_close(y, v.y) && are_close(z, v.z);
  }
  
};

struct Point{

};

#endif
