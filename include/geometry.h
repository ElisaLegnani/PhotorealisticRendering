/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software. THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include "functions.h"
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

// Scalar product
template <typename In1, typename In2> float _dot(const In1 &a, const In2 &b) {
  return {a.x * b.x + a.y * b.y + a.z * b.z};
}

// Normalized scalar product
template <typename In1, typename In2> float _normalized_dot(const In1 &a, const In2 &b) {
  In1 a_n = (In1(a)).normalize();
  In2 b_n = (In2(b)).normalize();
  return {a_n.x * b_n.x + a_n.y * b_n.y + a_n.z * b_n.z};
}

// Vector product
template <typename In1, typename In2, typename Out>
Out _cross(const In1 &a, const In2 &b) {
  return Out{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
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

  /**
   * @return the index corresponding to a coordinate
   */
  float operator[](int i) {
    if (i == 0) return x;
		else if (i == 1) return y;
    else if (i == 2) return z;
    else abort();
	}
  
  bool is_close(Vec v) {
    return are_close(x, v.x) && are_close(y, v.y) && are_close(z, v.z);
  }

  string get_string(){ return xyz_string("Vec",x,y,z);}

  float squared_norm() { return x*x + y*y + z*z; } //  ||v||2

  float norm() { return sqrt(this->squared_norm()); } //  ||v||

  Vec normalize() { // v -> v/||v||
    float norm = this->norm();
    return Vec(x /= norm, y /= norm, z /= norm);
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

inline float dot(const Vec &v1, const Vec &v2) { return _dot<Vec, Vec>(v1, v2); }

inline float normalized_dot(const Vec &v1, const Vec &v2) { return _normalized_dot<Vec, Vec>(v1, v2); }

inline Vec cross(const Vec &v1, const Vec &v2) { return _cross<Vec, Vec, Vec>(v1, v2); }


//–––––––––––––––––––––– Struct Point –––––––––––––––––––––––––––––––––––

struct Point {
  float x, y, z;

  Point(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  
  Point(const Point &pc) : x{pc.x}, y{pc.y}, z{pc.z} {} // Copy constructor
  Point(const Point &&pm) : x{pm.x}, y{pm.y}, z{pm.z} {} // Move constructor
  
  Point& operator=(const Point &p){ x=p.x; y=p.y; z=p.z; return *this; } // Assignment operator

  /**
   * @return the index corresponding to a coordinate
   */
  float operator[](int i) {
    if (i == 0) return x;
		else if (i == 1) return y;
    else if (i == 2) return z;
    else abort();
	}
  
  bool is_close(Point p) {
    return are_close(x, p.x) && are_close(y, p.y) && are_close(z, p.z);
  }

  string get_string(){ return xyz_string("Point",x,y,z);}
  
  Vec to_vec(){return Vec(x,y,z);}
  
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

inline Point operator-(const Point &p) { return p * (-1); } //?

inline Vec operator-(const Point &p1, const Point &p2) {
  return _diff<Point, Point, Vec>(p1, p2);
}


//–––––––––––––––––––––– Struct Normal –––––––––––––––––––––––––––––––––––

struct Normal {
  float x, y, z;

  Normal(float X = 0, float Y = 0, float Z = 0) : x{X}, y{Y}, z{Z} {}
  Normal(const Normal &nc)  : x{nc.x}, y{nc.y}, z{nc.z} {} // Copy constructor
  Normal(const Normal &&nm) : x{nm.x}, y{nm.y}, z{nm.z} {} // Move constructor

  Normal& operator=(const Normal &n){  x=n.x; y=n.y; z=n.z; return *this; } // Assignment operator

  /**
   * @return the index corresponding to a coordinate
   */
  float operator[](int i) {
    if (i == 0) return x;
		else if (i == 1) return y;
    else if (i == 2) return z;
    else abort();
	}
  
  bool is_close(Normal n) {
    return are_close(x, n.x) && are_close(y, n.y) && are_close(z, n.z);
  }

  string get_string() { return xyz_string("Normal",x,y,z);}

  float squared_norm() { return x*x + y*y + z*z; } //  ||v||2

  float norm() { return sqrt(this->squared_norm()); } //  ||v||

  Normal normalize() { // v -> v/||v||
    float norm = this->norm();
    return Normal(x /= norm, y /= norm, z /= norm);
  }

};

inline Normal operator-(const Normal &n) { return _prod<Normal, Normal>(n, -1.0); }

inline Normal operator*(const Normal &n, const float &c) { return _prod<Normal, Normal>(n, c); }

inline float dot(const Normal &n1, const Normal &n2) { return _dot<Normal, Normal>(n1, n2); }

inline float normalized_dot(const Normal &n1, const Normal &n2) { return _normalized_dot<Normal, Normal>(n1, n2); }

inline Normal cross(const Normal &n1, const Normal &n2) { return _cross<Normal, Normal, Normal>(n1, n2); }

inline float dot(const Vec &v, const Normal &n) { return _dot<Vec, Normal>(v, n); }

inline float normalized_dot(const Vec &v1, const Normal &n2) { return _normalized_dot<Vec, Normal>(v1, n2); }

inline Vec cross(const Vec &v, const Normal &n) { return _cross<Vec, Normal, Vec>(v, n); }

inline Vec operator+(const Vec &v, const Normal &n) {
  return _sum<Vec, Normal, Vec>(v, n);
}

inline Vec operator-(const Vec &v, const Normal &n) {
  return _diff<Vec, Normal, Vec>(v, n);
}



/**
 * A 2D vector representing a point on a surface
 * 
 * @param u
 * @param v
 */
struct Vec2d {

  float u;
  float v;
  
  Vec2d(float U=0.0, float V=0.0) : u(U),v(V){}

  bool is_close(Vec2d vec) {
    return are_close(u, vec.u) && are_close(v, vec.v);
  }
  string get_string(){
    return string{"Vec2d(" + to_string(u) + ", " + to_string(v) +")"};
  }
};

struct ONB {

  Vec e1, e2, e3;

  ONB(float x, float y, float z) {

    float sign;
    if (z > 0.0)
      sign = 1.0;
    else 
      sign = -1.0;

    float a = -1.0 / (sign + z);
    float b = x * y * a;

    e1 = Vec(1.0 + sign * x * x * a, sign * b, -sign * x);
    e2 = Vec(b, sign + y * y * a, -y);
    e3 = Vec(x, y, z);
  }

  ONB(Normal normal) : ONB(normal.x, normal.y, normal.z) {}

  ONB(Vec normal) : ONB(normal.x, normal.y, normal.z) {} // Normalized vector

};

#endif
