#include <iostream>
#include <vector>
#include "colors.h"

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage {

public:
  int width, height;
  vector<Color> pixels;

  HdrImage(int w, int h){};

  ~HdrImage(){};

  bool valid_coordinates(int x, int y) {
   return((x>=0) && (x<width) && (y>=0) && (y<height)); 
  }
  
  int pixel_offset(int x,int y){
    return y * width + x;
  }

};

#endif
