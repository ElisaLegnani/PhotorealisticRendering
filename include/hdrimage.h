#include "colors.h"

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage {

public:
  int width, height;
  vector<Color> pixels;

  HdrImage(){}

  ~HdrImage(){};

  HdrImage valid_coordinates(vector<Color> p, float x, float y) {
    
  }

};

#endif