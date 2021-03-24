#include "colors.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "write_float.h"

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

class HdrImage { // reminder: 1. width 2. height

public:
  int width;
  int height;
  string endianness="-1.0";
  vector<Color> pixels;

  HdrImage(){};

  HdrImage(int w, int h) {
    width = w;
    height = h;
    pixels.resize(width * height);
  }

  ~HdrImage(){};

  bool valid_coordinates(int x, int y) {
    return ((x >= 0) && (x < width) && (y >= 0) && (y < height));
  }

  int pixel_offset(int x, int y) { return y * width + x; }

  Color get_pixel(int x, int y) {
    if (valid_coordinates(x, y)) {
      return pixels[pixel_offset(x, y)];
    } else {
      abort();
    }
  }

  void set_pixel(int x, int y, Color new_color) {
    if (valid_coordinates(x, y)) {
      pixels[pixel_offset(x, y)] = new_color;
    } else {
      abort();
    }
  }
  
  void save_pfm(stringstream sstr){
    sstr << "PF\n" << width << " " << height << "\n" << endianness;
    string result{sstr.str()}; // perchè parentesi graffe? string result (sstr.str())
    
    for(int y=(height-1); y>=0; y--){
      for(int x=0; x<width; x++){
        Color color=pixels[x,y];
        write_float(sstr, color.m_r, Endianness::little_endian);
        write_float(sstr, color.m_g, Endianness::little_endian);
        write_float(sstr, color.m_b, Endianness::little_endian);
      }
    }
  }
};

#endif
