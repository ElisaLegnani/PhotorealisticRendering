#include "colors.h"
#include "hdrimage.h"
#include <cstdlib>


int main() {

  HdrImage img(7,4);

  if(img.pixel_offset(0, 0) != 0 || img.pixel_offset(3, 2) != 17 || img.pixel_offset(6, 3) != (7 * 4 - 1)){
    abort();
  }
  
  return 0;
}

//Oppure
//return (c1 * c2).is_color_close(Color{5.0, 14.0, 27.0}) ? EXIT_SUCCESS
//                                                        : EXIT_FAILURE;
