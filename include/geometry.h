/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "functions.h"
#include <iostream>
#include <sstream>

#define EPSILON 1e-4

using namespace std;

#ifndef _geometry_h_
#define _geometry_h_

//–––––––––– Templates supporting same operations for different geometric objects –––––––––––––––––––––––––––––

// Sum
template <typename In1, typename In2, typename Out>
Out _sum(const In1 &a, const In2 &b) {
  return Out{a.x + b.x, a.y + b.y, a.z + b.z};
}

// Difference
template <typename In1, typename In2, typename Out>
Out _diff(const In1 &a, const In2 &b) {
  return Out{a.x - b.x, a.y - b.y, a.z - b.z};
}

// Product
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
  (In1(a)).normalize();
  (In2(b)).normalize();
  return {a.x * b.x + a.y * b.y + a.z * b.z};
}

// Vector product
template <typename In1, typename In2, typename Out>
Out _cross(const In1 &a, const In2 &b) {
  return Out{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

/**
 Check if two geometric objects are to be considered the same (default deviation between coordinates < 1e-4).
 Needed to avoid floating-point approximation limits.
 */
template <typename In> bool are_xyz_close(const In &a, const In &b, float epsilon = EPSILON){
  return are_close(a.x, b.x, epsilon) && are_close(a.y, b.y, epsilon) && are_close(a.z, b.z, epsilon);
}

/**
 Create a printable string of the geometric object (Point, Vec, Normal)
 */
inline string xyz_string(string type, float x, float y, float z){
  return string{type+"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")"};
}

inline bool check_if_normalized(float x, float y, float z) {
  float norm = sqrt(x*x + y*y + z*z);
  if (are_close(x, x/norm) && are_close(y, y/norm) && are_close(z, z/norm)) return true;
  else return false;
}
 
//–––––––––––––––––––––– Struct Vec –––––––––––––––––––––––––––––––––––
/**
 * A 3D vector, identified by the three coordinates in space (floating-point parameters):
 * @param x
 * @param y
 * @param z
 */
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
  
  /**
   Check if the vector has roughly the same direction as the given one.
   Needed to avoid floating-point approximation limits.
   */
  bool is_close(Vec v, float epsilon = EPSILON) {
    return are_close(x, v.x, epsilon) && are_close(y, v.y, epsilon) && are_close(z, v.z, epsilon);
  }

  /**
   Return a printable string in form of "Vec(x,y,z)"
   */
  string get_string(){ return xyz_string("Vec",x,y,z);}

  /**
   Return the squared norm (Euclidean length) of a vector
   */
  float squared_norm() { return x*x + y*y + z*z; } //  ||v||2

  /**
   Return the norm (Euclidean length) of a vector
   */
  float norm() { return sqrt(this->squared_norm()); } //  ||v||

  /**
   Return the corrisponding versor (i.e. normalised vector)
   */
  Vec normalize() { // v -> v/||v||
    float norm = this->norm();
    return Vec(x /= norm, y /= norm, z /= norm);
  }

};

//––––––– Operations with Vec –––––––––––––––––––––––––––––––––––
/**
 Sum between two 'Vec'
 */
inline Vec operator+(const Vec &v1, const Vec &v2) {
  return _sum<Vec, Vec, Vec>(v1, v2);
}

/**
 Difference between two 'Vec'
 */
inline Vec operator-(const Vec &v1, const Vec &v2) {
  return _diff<Vec, Vec, Vec>(v1, v2);
}

/**
 Multiplication between a'Vec' and a scalar
 
 @return resized vector
 */
inline Vec operator*(const Vec &v1, const float &c) { return _prod<Vec, Vec>(v1, c); }
inline Vec operator*(const float &c, const Vec &v1) { return v1 * c; }

/**
 Reversed vector
 */
inline Vec operator-(const Vec &v) { return v * (-1); }

/**
 Scalar product between two 'Vec'
 
 @return floating-point result
 */
inline float dot(const Vec &v1, const Vec &v2) { return _dot<Vec, Vec>(v1, v2); }

/**
 Scalar product between the two versors of the given 'Vec'
 
 @return floating-point result
 */
inline float normalized_dot(const Vec &v1, const Vec &v2) { return _normalized_dot<Vec, Vec>(v1, v2); }

/**
 Vector product between two 'Vec'
 
 @return resulting 'Vec'
 */
inline Vec cross(const Vec &v1, const Vec &v2) { return _cross<Vec, Vec, Vec>(v1, v2); }


//–––––––––––––––––––––– Struct Point –––––––––––––––––––––––––––––––––––
/**
 * A point in 3D space, identified by the three coordinates in space (floating-point parameters):
 * @param x
 * @param y
 * @param z
 */
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
  
  /**
   Check if the point is roughly in the same position as the given one.
   Needed to avoid floating-point approximation limits.
   */
  bool is_close(Point p, float epsilon = EPSILON) {
    return are_close(x, p.x) && are_close(y, p.y) && are_close(z, p.z);
  }

  /**
   Return a printable string in form of "Point(x,y,z)"
   */
  string get_string(){ return xyz_string("Point",x,y,z);}
  
  /**
   Convert a 'Point' into a 'Vec'
   */
  Vec to_vec(){return Vec(x,y,z);}
  
};

//––––––– Operations with Point –––––––––––––––––––––––––––––––––––
/**
 Sum between a 'Point' and a 'Vec'
 
 @return point in the new position
 */
inline Point operator+(const Point &p, const Vec &v) {
  return _sum<Point, Vec, Point>(p, v);
}

/**
 Difference between a 'Point' and a 'Vec'
 
 @return point in the new position
 */
inline Point operator-(const Point &p, const Vec &v) {
  return _diff<Point, Vec, Point>(p, v);
}

/**
 Difference between two 'Point'
 
 @return resulting vector
 */
inline Vec operator-(const Point &p1, const Point &p2) {
  return _diff<Point, Point, Vec>(p1, p2);
}

/**
 Multiplication between a'Point' and a scalar
 
 @return point in the new position
 */
inline Point operator*(const Point &p, const float &c) { return _prod<Point, Point>(p, c); }
inline Point operator*(const float &c, const Point &p) { return p * c; }

/**
 Return the point in the opposite quadrant
 */
inline Point operator-(const Point &p) { return p * (-1); } //?


//–––––––––––––––––––––– Struct Normal –––––––––––––––––––––––––––––––––––
/**
 * A 3D normal vector
 *
 * Floating-point parameters:
 * @param x
 * @param y
 * @param z
 */
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
  
  /**
   Check if the vector has roughly the same direction as the given one.
   Needed to avoid floating-point approximation limits.
   */
  bool is_close(Normal n, float epsilon = EPSILON) {
    return are_close(x, n.x, epsilon) && are_close(y, n.y, epsilon) && are_close(z, n.z, epsilon);
  }

  /**
   Return a printable string in the form of "Normal(x,y,z)"
   */
  string get_string() { return xyz_string("Normal",x,y,z);}


  /**
   Return the squared norm (Euclidean length) of a normal
   */
  float squared_norm() { return x*x + y*y + z*z; } //  ||n||2

  /**
   Return the norm (Euclidean length) of a normal
   */
  float norm() { return sqrt(this->squared_norm()); } //  ||n||

  /**
   Return the corrisponding versor  (i.e. normalised normal)
   */
  Normal normalize() { // v -> v/||v||
    float norm = this->norm();
    return Normal(x /= norm, y /= norm, z /= norm);
  }

};

//––––––– Operations with Normal –––––––––––––––––––––––––––––––––––
/**
 Reversed normal (from external to internal, and vice versa)
 */
inline Normal operator-(const Normal &n) { return _prod<Normal, Normal>(n, -1.0); }

/**
 Multiplication between a'Normal' and a scalar
 
 @return resized normal
 */
inline Normal operator*(const Normal &n, const float &c) { return _prod<Normal, Normal>(n, c); }

/**
 Scalar product between two 'Normal'
 
 @return floating-point result
 */
inline float dot(const Normal &n1, const Normal &n2) { return _dot<Normal, Normal>(n1, n2); }

/**
 Scalar product between the two versors of the given 'Normal'
 
 @return floating-point result
 */
inline float normalized_dot(const Normal &n1, const Normal &n2) { return _normalized_dot<Normal, Normal>(n1, n2); }

/**
 Sum between a 'Vec' and a 'Normal'
 
 @return resulting 'Vec'
 */
inline Vec operator+(const Vec &v, const Normal &n) {
  return _sum<Vec, Normal, Vec>(v, n);
}

/**
 Difference between a 'Vec' and a 'Normal'
 
 @return resulting 'Vec'
 */
inline Vec operator-(const Vec &v, const Normal &n) {
  return _diff<Vec, Normal, Vec>(v, n);
}
/**
 Vector product between two 'Normal'
 
 @return resulting 'Normal'
 */
inline Normal cross(const Normal &n1, const Normal &n2) { return _cross<Normal, Normal, Normal>(n1, n2); }

/**
 Scalar product between a 'Vec' and a 'Normal'
 
 @return floating-point result
 */
inline float dot(const Vec &v, const Normal &n) { return _dot<Vec, Normal>(v, n); }

/**
 Scalar product between the two versors of the given 'Vec' and 'Normal'
 
 @return floating-point result
 */
inline float normalized_dot(const Vec &v1, const Normal &n2) { return _normalized_dot<Vec, Normal>(v1, n2); }

/**
 Vector product between a 'Vec' and a 'Normal'
 
 @return resulting 'Normal'
 */
inline Vec cross(const Vec &v, const Normal &n) { return _cross<Vec, Normal, Vec>(v, n); }



//–––––––––––––––––––––– Struct Vec2d –––––––––––––––––––––––––––––––––––
/**
 * A 2D vector representing a point on a surface
 *
 * Floating-point coordinates:
 * @param u
 * @param v
 */
struct Vec2d {

  float u;
  float v;
  
  Vec2d(float U=0.0, float V=0.0) : u(U),v(V){}

  /**
   Check if the 'Vec2d' corresponds roughly to the given one.
   Needed to avoid floating-point approximation limits.
   */
  bool is_close(Vec2d vec) {
    return are_close(u, vec.u) && are_close(v, vec.v);
  }
  /**
   Return a printable string in the form of "Vec2d(u,v)"
   */
  string get_string(){
    return string{"Vec2d(" + to_string(u) + ", " + to_string(v) +")"};
  }
};


//–––––––––––––––––––––– Struct ONB –––––––––––––––––––––––––––––––––––
/**
 * An ortonormal basis (ONB) created from a normalized vector representing the z axis
 * Note: Input vector/normal must be normalized.
 *
 * Parameters representing the three vectors of the basis:
 * @param e1
 * @param e2
 * @param e3
 */
struct ONB {

  private:

    void create_onb(float x, float y, float z) {

      if (!check_if_normalized(x, y, z)) {
        cerr << "Error: the vector or normal for creating an ONB must be normalized" << endl;
        abort();

      } else {

        float sign = copysignf(1.,z);

        float a = -1.0 / (sign + z);
        float b = x * y * a;

        e1 = Vec(1.0 + sign * x * x * a, sign * b, -sign * x);
        e2 = Vec(b, sign + y * y * a, -y);
        e3 = Vec(x, y, z);

      }
    }

  public:

    Vec e1, e2, e3;

    ONB(float x, float y, float z) {
      create_onb(x, y, z);
    }

    ONB(Normal normal) : ONB(normal.x, normal.y, normal.z) {}

    ONB(Vec normal) : ONB(normal.x, normal.y, normal.z) {} // Normalized vector

};

#endif
