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

struct Vec{
  float x, y, z;
      
      Vec(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
      Vec(const Vec &); // Copy constructor
      Vec(const Vec &&); // Move constructor
};

struct Point{

};

#endif
