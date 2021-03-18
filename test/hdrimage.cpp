#include "colors.h"
#include "hdrimage.h"
#include <cstdlib>


int main() {

  HdrImage img(7,4);

  if(img.valid_coordinates(1, 1) == 0){
    abort();
  }
  
  if(img.pixel_offset(0, 0) != 0 || img.pixel_offset(3, 2) != 17 || img.pixel_offset(6, 3) != (7 * 4 - 1)){
    abort();
  }
  
  return 0;
}
