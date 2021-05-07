#include "colors.h"
#include <iostream>

using namespace std;

int main() {

  Color c1(1.0, 2.0, 3.0);
  Color c2(5.0, 7.0, 9.0);
  float x = 5.0;

  if ((c1 + c2).is_color_close(Color(6.0, 9.0, 12.0)) == 0 ||
      (c2 - c1).is_color_close(Color(4.0, 5.0, 6.0)) == 0  ||
      (c1 * c2).is_color_close(Color(5.0, 14.0, 27.0)) == 0 ||
      (c1 * x).is_color_close(Color(5.0, 10.0, 15.0)) == 0){
    cout << "Error: color operators not working properly." << endl;    
    abort();
  }

  // Test luminosity

  if (are_close(c1.luminosity(), 2) == 0 || are_close(c2.luminosity(), 7) == 0) {
    cout << "Error: luminosity() method." << endl;
    abort();
  }

  return 0;
}