#include <iostream>
#include <vector>
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
  }

  ~HdrImage(){}
  
  bool valid_coordinates(int x, int y) {
   return((x>=0) && (x<width) && (y>=0) && (y<height));
  }
  
  int pixel_offset(int x, int y){
    return y * width + x;
  }
  
  Color get_pixel(int x, int y){
    if(valid_coordinates(x,y)){
      return pixels[pixel_offset(x,y)];
    }else{abort();}
  }
  
  void set_pixel(int x, int y, Color new_color){
    if(valid_coordinates(x,y)){
    pixels[pixel_offset(x,y)]=new_color;
    }else{abort();}
  }

};

#endif
