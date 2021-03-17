#include "colors.h"

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage { //reminder: 1. width 2. height

public:
  int width, height;
  vector<Color> pixels;

  HdrImage(int w, int h){
    width=w;
    height=h;
    pixels.resize(width*height);
  };

  ~HdrImage(){};
  
  bool valid_coordinates(vector<Color> p, int x, int y) {
    
  }
  
  int pixel_offset(int x, int y){
    return y * width + x;
  };
  
  


};

#endif
