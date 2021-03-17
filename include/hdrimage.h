#include "colors.h"

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage {

public:
  int width, height;
  std::vector<Color> pixels;

  HdrImage() {}

  ~HdrImage(){};
};

#endif