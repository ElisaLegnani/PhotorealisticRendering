#include "colors.h"
#include <cstdlib>


int main() {

  Color c1(1.0, 2.0, 3.0);
  Color c2(5.0, 7.0, 9.0);
  float x = 5.0;

  if ((c1 * c2).is_color_close(Color(5.0, 14.0, 27.0)) == 0) {
    abort();
  }
  if ((c1 * x).is_color_close(Color(5.0, 10.0, 15.0)) == 0) {
    abort();
  }
  
  return 0;
}

//Oppure
//return (c1 * c2).is_color_close(Color{5.0, 14.0, 27.0}) ? EXIT_SUCCESS
//                                                        : EXIT_FAILURE;