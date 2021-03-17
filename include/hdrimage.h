#include "colors.h"

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage {

public:
  int width, height;
  vector<Color> pixels;

  HdrImage(w,h){};

  ~HdrImage(){};

  bool valid_coordinates(float x, float y) {
   return((x>=0) && (x<widht) && (y>=0) && (y<heigh)); 
  }
  
  int pixel_offset(x,y){
    return y * width + x;
  }

};

#endif
