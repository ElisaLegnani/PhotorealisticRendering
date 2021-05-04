#include "transformation.h"
#include <algorithm>
#include <cstdlib>

int main() {

  Vec VEC_X(1.0, 0.0, 0.0);
  Vec VEC_Y(0.0, 1.0, 0.0);
  Vec VEC_Z(0.0, 0.0, 1.0);

/*test get_string da fare
  Transformation t1;
  cout << t1.get_string();
*/

  float m[4][4] = {{1.0, 2.0, 3.0, 4.0},
                    {5.0, 6.0, 7.0, 8.0},
                    {9.0, 9.0, 8.0, 7.0},
                    {6.0, 5.0, 4.0, 1.0}};
  
  float invm[4][4] = {{-3.75, 2.75, -1, 0},
                      {4.375, -3.875, 2.0, -0.5},
                      {0.5, 0.5, -1.0, 1.0},
                      {-1.375, 0.875, 0.0, -0.5}};

  Transformation t1(m, invm);


  // Test is_consistent

  if (t1.is_consistent() == 0) {
    cout << "Error: is_consistent()." << endl;
    abort();
  }


  // Test is_close

  Transformation t2(m, invm);

  if (t1.is_close(t2) == 0) {
    cout << "Error: is_close()." << endl;
    abort();
  }

  Transformation t3(m, invm);
  t3.m[2][2] += 1.0;

  if (t3.is_close(t1) != 0) {
    cout << "Error: is_close()." << endl;
    abort();
  }

  Transformation t4(m, invm);
  t4.invm[2][2] += 1.0;

  if (t4.is_close(t1) != 0) {
    cout << "Error: is_close()." << endl;
    abort();
  }
  

  // Test operator*

  float m2[4][4] = {{3.0, 5.0, 2.0, 4.0},
                    {4.0, 1.0, 0.0, 5.0},
                    {6.0, 3.0, 2.0, 0.0},
                    {1.0, 4.0, 2.0, 1.0}};
  
  float invm2[4][4] = {{0.4, -0.2, 0.2, -0.6},
                      {2.9, -1.7, 0.2, -3.1},
                      {-5.55, 3.15, -0.4, 6.45},
                      {-0.9, 0.7, -0.2, 1.1}};

  Transformation t5(m2, invm2);

  if (t5.is_consistent() == 0) {
    cout << "Error: is_consistent()." << endl;
    abort();
  }

  float m3[4][4] = {{33.0, 32.0, 16.0, 18.0},
                    {89.0, 84.0, 40.0, 58.0},
                    {118.0, 106.0, 48.0, 88.0},
                    {63.0, 51.0, 22.0, 50.0}};
  
  float invm3[4][4] = {{-1.45, 1.45, -1.0, 0.6},
                      {-13.95, 11.95, -6.5, 2.6},
                      {25.525, -22.025, 12.25, -5.2},
                      {4.825, -4.325, 2.5, -1.1}};
  
  Transformation t6(m3, invm3);

  if (t6.is_consistent() == 0) {
    cout << "Error: is_consistent()." << endl;
    abort();
  }

  if (t6.is_close(t1*t5) == 0) {
    cout << "Error: operator* (Transformation*Transformation)." << endl;
    abort();
  }
  
  float m4[4][4] = {{1.0, 2.0, 3.0, 4.0},
                    {5.0, 6.0, 7.0, 8.0},
                    {9.0, 9.0, 8.0, 7.0},
                    {0.0, 0.0, 0.0, 1.0}};
  
  float invm4[4][4] = {{-3.75, 2.75, -1, 0},
                      {5.75, -4.75, 2.0, 1.0},
                      {-2.25, 2.25, -1.0, -2.0},
                      {0.0, 0.0, 0.0, 1.0}};

  Transformation t7(m4, invm4);

  if (t7.is_consistent() == 0) {
    cout << "Error: is_consistent()." << endl;
    abort();
  }

  Vec v(14.0, 38.0, 51.0);

  if (v.is_close(t7 * Vec(1.0, 2.0, 3.0)) == 0) {
    cout << "Error: operator* (Transformation*Vec)." << endl;
    abort();
  }
  
  Point p(18.0, 46.0, 58.0);

  if (p.is_close(t7 * Point(1.0, 2.0, 3.0)) == 0) {
    cout << "Error: operator* (Transformation*Point)." << endl;
    abort();
  }

  Normal n(-8.75, 7.75, -3.0);

  if (n.is_close(t7 * Normal(3.0, 2.0, 4.0)) == 0) {
    cout << "Error: operator* (Transformation*Normal)." << endl;
    abort();
  }


  // Test inverse

  Transformation t8 = t1.inverse();

  if (t8.is_consistent() == 0) {
    cout << "Error: inverse()." << endl;
    abort();
  }

  
  Transformation prod = t1 * t8;
    
  if (prod.is_consistent() == 0) {
    cout << "Error: inverse()." << endl;
    abort();
  }
  
  if (prod.is_close(t1) != 0) {
    cout << "Error: inverse()." << endl;
    abort();
  }


  // Test translation

  Transformation tr1 = translation(Vec(1.0, 2.0, 3.0));
        
  if (tr1.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
  
  
  Transformation tr2 = translation(Vec(4.0, 6.0, 8.0));
  
  if (tr2.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
        
  Transformation prod2 = tr1 * tr2;

  if (prod2.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
  
  Transformation tr3 = translation(Vec(5.0, 8.0, 11.0));

  if (prod2.is_close(tr3) == 0) {
    cout << "Error: transflation() or matrix product operator." << endl;
    abort();
  }
  
  // Test scaling
  
  Transformation sc1=scaling(Vec(2.0,5.0,10.0));
  
  if (sc1.is_consistent() == 0) {
    cout << "Error: scaling()." << endl;
    abort();
  }
  
  Transformation sc2=scaling(Vec(3.0,2.0,4.0));
  
  if (sc2.is_consistent() == 0) {
    cout << "Error: scaling()." << endl;
    abort();
  }
  
  Transformation sc3=scaling(Vec(6.0,10.0,40.0));
  Transformation prod3=sc1*sc2;
  
  if (prod3.is_close(sc3) == 0) {
    cout << "Error: scaling() or matrix product operator." << endl;
    abort();
  }

// Test rotations

Transformation rx1=rotation_x(0.1);
Transformation ry1=rotation_y(0.1);
Transformation rz1=rotation_z(0.1);

if (rx1.is_consistent() == 0 | ry1.is_consistent() == 0 | rz1.is_consistent() == 0) {
  cout << "Error: rotation_*()." << endl;
  abort();
}
  
  Transformation rx2=rotation_x(M_PI*0.5);
  Transformation ry2=rotation_y(M_PI*0.5);
  Transformation rz2=rotation_z(M_PI*0.5);

if ((rx2*VEC_Y).is_close(VEC_Z) == 0 | (ry2*VEC_Z).is_close(VEC_X) == 0 | (rz2*VEC_X).is_close(VEC_Y) == 0) {
  cout << "Error: rotation_*()." << endl;
  abort();
}

return 0;
}
