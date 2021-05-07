#include "functions.h"
#include <cmath>
#include <iostream>
#include <sstream>

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

template <typename In> bool are_xyz_close(const In &a, const In &b){
  return are_close(a.x, b.x) && are_close(a.y, b.y) && are_close(a.z, b.z);
}

inline string xyz_string(string type, float x, float y, float z){
  return string{type+"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"};
 }

 
//–––––––––––––––––––––– Struct Vec –––––––––––––––––––––––––––––––––––

struct Vec {
  float x, y, z;

  Vec(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}

  Vec(const Vec &vc): x{vc.x}, y{vc.y}, z{vc.z} {} // Copy constructor: Vec t=t2
  Vec(const Vec &&vm) : x{vm.x}, y{vm.y}, z{vm.z} {} // Move constructor
  
  Vec& operator=(const Vec &v){x=v.x; y=v.y; z=v.z; return *this;} // Assignment operator: Vec v2; v2=v1
  
  bool is_close(Vec v) {
    return are_close(x, v.x) && are_close(y, v.y) && are_close(z, v.z);
  }

  string get_string(){ return xyz_string("Vec",x,y,z);}

  float squared_norm() { return x*x + y*y + z*z; } //  ||v||2

  float norm() { return sqrt(this->squared_norm()); } //  ||v||

  void normalize() { // v -> v/||v||
    float norm = this->norm();
    x /= norm;
    y /= norm;
    z /= norm;
  }
};

inline Vec operator+(const Vec &v1, const Vec &v2) {
  return _sum<Vec, Vec, Vec>(v1, v2);
}

inline Vec operator-(const Vec &v1, const Vec &v2) {
  return _diff<Vec, Vec, Vec>(v1, v2);
}

inline Vec operator*(const Vec &v1, const float &c) { return _prod<Vec, Vec>(v1, c); }
inline Vec operator*(const float &c, const Vec &v1) { return v1 * c; }

inline Vec operator-(const Vec &v) { return v * (-1); }

// Scalar product
inline float dot(const Vec &v1, const Vec &v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

// Vector product
inline Vec cross(const Vec &v1, const Vec &v2) {
  return Vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}


//–––––––––––––––––––––– Struct Point –––––––––––––––––––––––––––––––––––

struct Point {
  float x, y, z;

  Point(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  
  Point(const Point &pc) : x{pc.x}, y{pc.y}, z{pc.z} {} // Copy constructor
  Point(const Point &&pm) : x{pm.x}, y{pm.y}, z{pm.z} {} // Move constructor
  
  Point& operator=(const Point &p){ x=p.x; y=p.y; z=p.z; return *this; } // Assignment operator
  
  bool is_close(Point p) {
    return are_close(x, p.x) && are_close(y, p.y) && are_close(z, p.z);
  }

  string get_string(){ return xyz_string("Point",x,y,z);}
  
};

inline Point operator+(const Point &p, const Vec &v) {
  return _sum<Point, Vec, Point>(p, v);
}

inline Point operator-(const Point &p, const Vec &v) {
  return _diff<Point, Vec, Point>(p, v);
}

inline Point operator*(const Point &p, const float &c) {
  return _prod<Point, Point>(p, c);
}
inline Point operator*(const float &c, const Point &p) { return p * c; }

inline Point operator-(const Point &p) { return p * (-1); }

inline Vec operator-(const Point &p1, const Point &p2) {
  return _diff<Point, Point, Vec>(p1, p2);
}


//–––––––––––––––––––––– Struct Normal –––––––––––––––––––––––––––––––––––

struct Normal {
  float x, y, z;

  Normal(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  Normal(const Normal &nc)  : x{nc.x}, y{nc.y}, z{nc.z} {} // Copy constructor
  Normal(const Normal &&nm) : x{nm.x}, y{nm.y}, z{nm.z} {} // Move constructor

  Normal& operator=(const Normal &n){ return *this; } // Assignment operator
  
  bool is_close(Normal n) {
    return are_close(x, n.x) && are_close(y, n.y) && are_close(z, n.z);
  }

  string get_string() { return xyz_string("Normal",x,y,z);}

};

#endif
