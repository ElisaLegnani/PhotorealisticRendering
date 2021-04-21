#include "geometry.h"
#include <cstdlib>

int main() {

  Vec v1(1.0, 2.0, 3.0);
  Vec v2(4.0, 6.0, 8.0);

  if ((v1.is_close(v1) == 0) || (v1.is_close(v2) != 0)) {
    cout << "Error: constructor sets wrong vector coordinates." << endl;
    abort();
  }

  if (((v1 + v2).is_close(Vec(5.0, 8.0, 11.0)) == 0) ||
      ((v2 - v1).is_close(Vec(3.0, 4.0, 5.0)) == 0) ||
      ((2 * v1).is_close(Vec(2.0, 4.0, 6.0)) == 0) ||
      ((v1 * 2).is_close(Vec(2.0, 4.0, 6.0)) == 0)) {
    cout << "Error: vector operators not working properly." << endl;
    abort();
  }

  return 0;
}
