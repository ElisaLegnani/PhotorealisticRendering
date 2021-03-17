#include "colors.h"
#include "hdrimage.h"
#include <cstdlib>


int main() {

  HdrImage img;
  
  if ((c2 - c1).is_color_close(Color(4.0, 5.0, 6.0)) == 0) {
    abort();
  }
  
  return 0;
}

//Oppure
//return (c1 * c2).is_color_close(Color{5.0, 14.0, 27.0}) ? EXIT_SUCCESS
//                                                        : EXIT_FAILURE;
