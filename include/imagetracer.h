#include "hdrimage.h"
#include "camera.h"

#ifndef _imageracer_h_
#define _imagetracer_h_

struct ImageTracer {

  HdrImage image;
  Camera &camera; //giusto? altrimenti: cannot declare parameter ‘cam’ to be of abstract type ‘Camera’

  ImageTracer(HdrImage img, Camera &cam): image{img}, camera{cam} {};

  Ray fire_ray(int col, int row, int u_pixel=0.5, int v_pixel=0.5){
    float u = (col + u_pixel) / image.width;
    float v = 1.0 - (row + v_pixel) / image.height;
    return camera.fire_ray(u,v);
  }

  //fire_all_rays(function){}

  
};

#endif