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

  HdrImage valid_coordinates(vector<Color> pixels, float x, float y) {
    return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b);
  }

};

#endif