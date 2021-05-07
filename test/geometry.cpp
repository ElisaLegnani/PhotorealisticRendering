#include "geometry.h"

int main() {

  // –––––––––––––––– Test Vec

  Vec v1(1.0, 2.0, 3.0);
  Vec v2(4.0, 6.0, 8.0);
  Vec v3(v1);
  Vec v4=move(v1);
 
  if (v1.is_close(v1) == 0 || v1.is_close(v2) != 0) {
    cout << "Error: Vec constructor or is_close()." << endl;
    abort();
  }
  
  if (v1.is_close(v3) == 0) {
    cout << "Error: Vec copy constructor." << endl;
    abort();
  }
  
  if (v1.is_close(v4) == 0) {
    cout << "Error: Vec move constructor." << endl;
    abort();
  }
  
  v3=v2;
  if (v2.is_close(v3) == 0) {
    cout << "Error: Vec assignment operator." << endl;
    abort();
  }

  if ((-v1).is_close(Vec(-1.0, -2.0, -3.0)) == 0 ||
      (v1 + v2).is_close(Vec(5.0, 8.0, 11.0)) == 0 ||
      (v2 - v1).is_close(Vec(3.0, 4.0, 5.0)) == 0 ||
      (2 * v1).is_close(Vec(2.0, 4.0, 6.0)) == 0 ||
      (v1 * 2).is_close(Vec(2.0, 4.0, 6.0)) == 0 ||
      are_close(dot(v1, v2), 40.0) == 0 ||
      (cross(v1, v2)).is_close(Vec(-2.0, 4.0, -2.0)) == 0 ||
      (cross(v2, v1)).is_close(Vec(2.0, -4.0, 2.0)) == 0 ||
      are_close(v1.squared_norm(), 14.0) == 0 ||
      are_close(pow(v1.norm(),2), 14.0 == 0)
      ){
    cout << "Error: Vec operators not working properly." << endl;
    abort();
  }



  // –––––––––––––––– Test Point

  Point p1(1.0, 2.0, 3.0);
  Point p2(4.0, 6.0, 8.0);
  Point p3=p1;
  Point p4=move(p1);
  
  if (p1.is_close(p1) == 0 || p1.is_close(p2) != 0) {
    cout << "Error: Point constructor or is_close()." << endl;
    abort();
  }
  
  if (p1.is_close(p3) == 0) {
    cout << "Error: Point copy constructor." << endl;
    abort();
  }
  if (p1.is_close(p4) == 0) {
    cout << "Error: Point move constructor." << endl;
    abort();
  }
  
  p3=p2;
  if (p2.is_close(p3) == 0) {
    cout << "Error: Point assignment operator." << endl;
    abort();
  }

  if ((-p1).is_close(Point(-1.0, -2.0, -3.0)) == 0 ||
      (p1 * 2).is_close(Point(2.0, 4.0, 6.0)) == 0 ||
      (p1 + v2).is_close(Point(5.0, 8.0, 11.0)) == 0 ||
      (p2 - p1).is_close(Vec(3.0, 4.0, 5.0)) == 0 ||
      (p1 - v2).is_close(Point(-3.0, -4.0, -5.0)) == 0) {
    cout << "Error: Point operators not working properly." << endl;
    abort();
  }
  

//  –––––––––––––––– Test are_xyz_close (as template)

  if (are_xyz_close(v1, v1) == 0 || are_xyz_close(v1, v2) != 0) {
    cout << "Error: are_xyz_close() with Vec." << endl;
    abort();
  }

  if (are_xyz_close((-v1), Vec(-1.0, -2.0, -3.0)) == 0 ||
      are_xyz_close((v1 + v2), Vec(5.0, 8.0, 11.0)) == 0 ||
      are_xyz_close((v2 - v1), Vec(3.0, 4.0, 5.0)) == 0 ||
      are_xyz_close((2 * v1), Vec(2.0, 4.0, 6.0)) == 0 ||
      are_xyz_close((v1 * 2), Vec(2.0, 4.0, 6.0)) == 0 ||
      are_close(dot(v1, v2), 40.0) == 0 ||
      are_xyz_close((cross(v1, v2)), Vec(-2.0, 4.0, -2.0)) == 0 ||
      are_xyz_close((cross(v2, v1)), Vec(2.0, -4.0, 2.0)) == 0 ||
      are_close(v1.squared_norm(), 14.0) == 0 ||
      are_close(pow(v1.norm(),2), 14.0) == 0
      ) {
    cout << "Error: Vec operators in are_xyz_close()." << endl;
    abort();
  }
  
  if (are_xyz_close(p1, p1) == 0 || are_xyz_close(p1, p2) != 0) {
    cout << "Error: are_xyz_close() with Point." << endl;
    abort();
  }

  if (are_xyz_close((-p1), Point(-1.0, -2.0, -3.0)) == 0 ||
      are_xyz_close((p1 * 2), Point(2.0, 4.0, 6.0)) == 0 ||
      are_xyz_close((p1 + v2), Point(5.0, 8.0, 11.0)) == 0 ||
      are_xyz_close((p2 - p1), Vec(3.0, 4.0, 5.0)) == 0 ||
      are_xyz_close((p1 - v2), Point(-3.0, -4.0, -5.0)) == 0) {
    cout << "Error: Point operators in are_xyz_close()." << endl;
    abort();
  }
  
  // –––––––––––––––– Test Normal

  Normal n1(1.0, 2.0, 3.0);
  Normal n2(4.0, 6.0, 8.0);
  Normal n3(n1);
  Normal n4=move(n1);
 
  if (n1.is_close(n1) == 0 || n1.is_close(n2) != 0) {
    cout << "Error: Normal constructor or is_close()." << endl;
    abort();
  }
  
  if (n1.is_close(n3) == 0) {
    cout << "Error: Normal copy constructor." << endl;
    abort();
  }
  
  if (n1.is_close(n4) == 0) {
    cout << "Error: Normal move constructor." << endl;
    abort();
  }
  
  n3=n2;
  if (n2.is_close(n3) == 0) {
    cout << "Error: Normal assignment operator." << endl;
    abort();
  }
  
  return 0;
}
