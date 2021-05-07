#include "hdrimage.h"
#include "camera.h"
#include "colors.h"
#include <functional>

#ifndef _imageracer_h_
#define _imagetracer_h_

struct ImageTracer {

  HdrImage image;
  Camera &camera;

  ImageTracer(HdrImage img, Camera &cam): image{img}, camera{cam} {};

  Ray fire_ray(int col, int row, float u_pixel=0.5, float v_pixel=0.5){
    float u = (col + u_pixel) / image.width;
    float v = 1.0 - (row + v_pixel) / image.height;
    return camera.fire_ray(u,v);
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
