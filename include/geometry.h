#include "colors.h"
#include <cmath>
#include <iostream>

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

template <typename In1, typename Out> Out _prod(const In1 &a, const float &b) {
  return Out{a.x * b, a.y * b, a.z * b};
}

/*bool are_xy_close(float x, float y) { //ha senso ridefinirla o usiamo
colors.h? float epsilon = 1e-10; return abs(x - y) < epsilon;
}*/

/*bool are_xyz_close(Vec v1, Vec v2) {
  return are_close(v1.x, v2.x) && are_close(v1.y, v2.y) && are_close(v1.z,
v2.z);
}*/

// Struct Vec

struct Vec {
  float x, y, z;

  Vec(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  // Vec(const Vec &); // Copy constructor
  // Vec(const Vec &&); // Move constructor

  bool is_close(Vec v) {
    return are_close(x, v.x) && are_close(y, v.y) && are_close(z, v.z);
  }

  string print_string() {
    return string{"Vec(" + to_string(x) + ", " + to_string(y) + ", " +
                  to_string(z) + ")"};
  }

  float squared_norm() { return x*x + y*y + z*z; }

  float norm() { return sqrt(squared_norm()); }

  void normalize() {
    float norm = norm();
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
float dot(const Vec &v1, const Vec &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Vector product
Vec cross(const Vec &v1, const Vec &v2) {
  return Vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
             v1.x * v2.y - v1.y * v2.x);
}

// Struct Point

struct Point {
  float x, y, z;

  Point(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  // Point(const Point &); // Copy constructor
  // Point(const Point &&); // Move constructor

  bool is_close(Point p) {
    return are_close(x, p.x) && are_close(y, p.y) && are_close(z, p.z);
  }

  string print_string() {
    return string{"Point(" + to_string(x) + ", " + to_string(y) + ", " +
                  to_string(z) + ")"};
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

// Struct Normal

struct Normal {
  float x, y, z;

  Normal(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
};

#endif
