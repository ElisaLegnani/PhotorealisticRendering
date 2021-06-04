/*
The MIT License (MIT)

Copyright © 2021 Elisa Legnani, Adele Zaini

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of
the Software. THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include "hdrimage.h"
#include "camera.h"
#include "colors.h"
#include <functional>
#include <iostream>
#include <memory>

#ifndef _imageracer_h_
#define _imagetracer_h_

struct ImageTracer {

  HdrImage image;
  shared_ptr<Camera> camera;

  ImageTracer(HdrImage img, shared_ptr<Camera> cam): image{img}, camera{cam} {};

  Ray fire_ray(int col, int row, float u_pixel=0.5, float v_pixel=0.5){
    float u = (col + u_pixel) / image.width;
    float v = 1.0 - (row + v_pixel) / image.height;
    return camera->fire_ray(u,v);
  }

  void fire_all_rays(function<Color(Ray)> func){
    for (int row{}; row<image.height; ++row){
      for(int col{};col<image.width;++col){
        Ray ray=fire_ray(col,row);
        Color color=func(ray);
        image.set_pixel(col,row,color);
      }
    }
  }

  
};

#endif
