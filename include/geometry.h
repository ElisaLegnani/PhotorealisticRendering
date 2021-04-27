#include "colors.h"
#include <cmath>
#include <iostream>

// CREARE GEOMETRY.CPP ?

using namespace std;

#ifndef _geometry_h_
#define _geometry_h_

template <typename In1, typename In2, typename Out>
Out _sum(const In1 &a, const In2 &b) {
  return Out{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename In1, typename In2, typename Out>
Out _diff(const In1 &a, const In2 &b) {
  return Out{a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename In1, typename Out>
Out _prod(const In1 &a, const float &b) {
  return Out{a.x * b, a.y * b, a.z * b};
}

/*template <typename In, typename Out> // Da controllare
Out _copy(const In &b) {
  return Out{b.x, b.y, b.z};
}*/

template <typename In> bool are_xyz_close(const In &a, const In &b){ //meglio con template! non ci sono problemi con copy e move constructors
  return are_close(a.x, b.x) && are_close(a.y, b.y) && are_close(a.z, b.z);
}

/* string print_string(string type, float x, float y, float z){ //poi possiamo chiamare print all'interno.
  return string{type+"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"}
 }
 Da usare: string print(){ return print_string("Vec",x,y,z)} */

 
//–––––––––––––––––––––– Struct Vec –––––––––––––––––––––––––––––––––––

struct Vec {
  float x, y, z;

  Vec(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  
  Vec(const Vec &); // Copy constructor
  Vec(const Vec &&); // Move constructor

  //Vec(const Vec &vc){ x=vc.x; y=vc.y; z=vc.z; } // Copy constructor da implementare in .cpp? // Vec(const Vec &); piu elegante, ma da verificare: Vec(const Vec &vc):Vec(*vc.x,*vc.y,*vc.z) {}
  //Vec(const Vec &&vm) : x{vm.x}, y{vm.y}, z{vm.z} {} // Move constructor // Vec(const Vec &&);
  //Move constructor: to create temporary objects for quick operations (no memory needed)
  
  // meglio con template
  /*bool is_close(Vec v) {
    return are_close(x, v.x) && are_close(y, v.y) && are_close(z, v.z);
  }*/ 

  string print_string() {
    return string{"Vec(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"};
  }

//  ||v||2
  float squared_norm() { return x*x + y*y + z*z; }

//  ||v||
  float norm() { return sqrt(this->squared_norm()); }

// v -> v/||v||
  void normalize() {
    float norm = this->norm();
    x /= norm;
    y /= norm;
    z /= norm;
  }
};

Vec operator+(const Vec &v1, const Vec &v2) {
  return _sum<Vec, Vec, Vec>(v1, v2);
}

Vec operator-(const Vec &v1, const Vec &v2) {
  return _diff<Vec, Vec, Vec>(v1, v2);
}

Vec operator*(const Vec &v1, const float &c) { return _prod<Vec, Vec>(v1, c); }
Vec operator*(const float &c, const Vec &v1) { return v1 * c; }

// Scalar product
float dot(const Vec &v1, const Vec &v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

// Vector product
Vec cross(const Vec &v1, const Vec &v2) {
  return Vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

/*Vec operator=(const Vec &v) {
  return _copy<Vec, Vec>(v);
}*/

//–––––––––––––––––––––– Struct Point –––––––––––––––––––––––––––––––––––

struct Point {
  float x, y, z;

  Point(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  Point(const Point &); // Copy constructor
  Point(const Point &&); // Move constructor

  // meglio con template
  /*bool is_close(Point p) {
    return are_close(x, p.x) && are_close(y, p.y) && are_close(z, p.z);
  }*/

  string print_string() {
    return string{"Point(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"};
  }
};

Point operator+(const Point &p, const Vec &v) {
  return _sum<Point, Vec, Point>(p, v);
}

Point operator-(const Point &p, const Vec &v) {
  return _diff<Point, Vec, Point>(p, v);
}

Point operator*(const Point &p, const float &c) {
  return _prod<Point, Point>(p, c);
}
Point operator*(const float &c, const Point &p) { return p * c; }

Vec operator-(const Point &p1, const Point &p2) {
  return _diff<Point, Point, Vec>(p1, p2);
}
/*
Point operator=(const Point &p) {
  return _copy<Point, Point>(p);
}*/

//–––––––––––––––––––––– Struct Normal –––––––––––––––––––––––––––––––––––

struct Normal {
  float x, y, z;

  Normal(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  Normal(const Normal &); // Copy constructor
  Normal(const Normal &&); // Move constructor

  // meglio con template
  /*bool is_close(Normal n) {
    return are_close(x, n.x) && are_close(y, n.y) && are_close(z, n.z);
  }*/

  string print_string() {
    return string{"Normal(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"};
  }
  
//  Da implementare anche le altre? - non credo
};

//–––––––––––––––––––––– Unit vectors i, j, k –––––––––––––––––––––––––––––––––––

Vec VEC_X(1.0, 0.0, 0.0);
Vec VEC_Y(0.0, 1.0, 0.0);
Vec VEC_Z(0.0, 0.0, 1.0);

#endif
