#include "transformation.h"
#include <algorithm>
#include <cstdlib>

int main() {

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


  // Test is_consistent()

  if (t1.is_consistent() == 0) {
    cout << "Error: is_consistent()." << endl;
    abort();
  }


  // Test is_close()

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
  

  // Test inverse

  Transformation t5 = t1.inverse();

  if (t5.is_consistent() == 0) {
    cout << "Error: inverse()." << endl;
    abort();
  }

  /*
  Transformation prod = t1 * t5;
    
  if (prod.is_consistent() == 0) {
    cout << "Error: inverse()." << endl;
    abort();
  }
  
  if (prod.is_close(t1) != 0) {
    cout << "Error: is_close()." << endl;
    abort();
  }
  */


  // Test translation

  Transformation tr1 = translation(Vec(1.0, 2.0, 3.0));
        
  if (tr1.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
  
  /*
  Transformation tr2 = translation(Vec(4.0, 6.0, 8.0));
  
  if (tr2.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
        
  Transformation prod = tr1 * tr2

  if (prod.is_consistent() == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
  
  Transformation tr3 = translation(Vec(5.0, 8.0, 11.0))

  if (prod.is_close(tr3) == 0) {
    cout << "Error: translation()." << endl;
    abort();
  }
  */

  return 0;
}
