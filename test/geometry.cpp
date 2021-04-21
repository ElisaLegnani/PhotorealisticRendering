#include "geometry.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {

  // Test Vec

  Vec v1(1.0, 2.0, 3.0);
  Vec v2(4.0, 6.0, 8.0);

  if ((v1.is_close(v1) == 0) || (v1.is_close(v2) != 0)) {
    cout << "Error: constructor sets wrong vector coordinates." << endl;
    abort();
  }

  if (//((-v1).is_close(Vec(-1.0, -2.0, -3.0)) == 0) ||
      ((v1 + v2).is_close(Vec(5.0, 8.0, 11.0)) == 0) ||
      ((v2 - v1).is_close(Vec(3.0, 4.0, 5.0)) == 0) ||
      ((2 * v1).is_close(Vec(2.0, 4.0, 6.0)) == 0) ||
      ((v1 * 2).is_close(Vec(2.0, 4.0, 6.0)) == 0) ||
      ((are_close(dot(v1, v2), 40.0)) == 0) ||
      (((cross(v1, v2)).is_close(Vec(-2.0, 4.0, -2.0))) == 0) ||
      (((cross(v2, v1)).is_close(Vec(2.0, -4.0, 2.0))) == 0) ||
      ((are_close(v1.squared_norm(), 14.0)) == 0) ||
      ((are_close(pow(v1.norm(),2), 14.0)) == 0)) {
    cout << "Error: vector operators not working properly." << endl;
    abort();
  }


  // Test Point

  Point p1(1.0, 2.0, 3.0);
  Point p2(4.0, 6.0, 8.0);

  if ((p1.is_close(p1) == 0) || (p1.is_close(p2) != 0)) {
    cout << "Error: constructor sets wrong point coordinates." << endl;
    abort();
  }

  if (((p1 * 2).is_close(Point(2.0, 4.0, 6.0)) == 0) ||
      ((p1 + v2).is_close(Point(5.0, 8.0, 11.0)) == 0) ||
      ((p2 - p1).is_close(Vec(3.0, 4.0, 5.0)) == 0) ||
      ((p1 - v2).is_close(Point(-3.0, -4.0, -5.0)) == 0)) {
    cout << "Error: point operators not working properly." << endl;
    abort();
  }

  return 0;
}
