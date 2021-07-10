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
#include "pcg.h"
#include <functional>
#include <iostream>
#include <memory>

#ifndef _imageracer_h_
#define _imagetracer_h_

/**
 * A struct that represents image tracing obtained by shooting rays through the image's pixels
 *
 * @param image HdrImage object already initialized
 * @param camera orthogonal or perspective camera
 * @param samples_per_size if larger than zero, it activates the stratified sampling algorithm 
 on each pixel of the image, that uses the random number generator pcg
 * @param pcg PCG object for random number generation
 */
struct ImageTracer {

  HdrImage image;
  shared_ptr<Camera> camera;
  int samples_per_side;
  PCG pcg;

  ImageTracer(HdrImage img, shared_ptr<Camera> cam, int samples = 0, PCG _pcg = PCG()): 
      image{img}, camera{cam}, samples_per_side{samples}, pcg{_pcg} {};

  /**
   * Shoot a ray through the given pixel (col,row)
   *
   * Integer parameters to identify the pixel:
   * @param col
   * @param row
   *
   *Floating-point parameters ranging [0,1] identifing which position the ray hits the choosen pixel.
   *Default values are 0.5, that identified the center of the pixel.
   *@param u_pixel
   *@param v_pixel
   *
   *@return a ray crossing the image pixel with the choosen camera projection
   */
  Ray fire_ray(int col, int row, float u_pixel=0.5, float v_pixel=0.5){
    float u = (col + u_pixel) / image.width;
    float v = 1.0 - (row + v_pixel) / image.height;
    return camera->fire_ray(u,v);
  }

  /**
   * Shoot all the rays through each image pixel and set the corrisponding color on the base of the choosen rendering algorithm.
   *
   * The passing argument is a function that accepts a 'Ray' as input and returns a 'Color', and depends on the choosen rendering algorithm.
   * For each pixel of the 'HdrImage', a 'Ray' is fired and passed to the function 'func', that evaluates the 'Color' of the shape hit (or background color if no hit happens).
   * It also implements the antialiasing algorithm to avoid Moirè pattern effect.
   */
  void fire_all_rays(function<Color(Ray)> func){

    for(int row{}; row<image.height; ++row){
      for(int col{}; col<image.width; ++col){

        Color cum_color = BLACK;

        if(samples_per_side > 0) {
          // Run stratified sampling over the pixel's surface
          for(int pixel_row{};  pixel_row<samples_per_side; ++pixel_row) {
            for(int pixel_col{};  pixel_col<samples_per_side; ++pixel_col) {
              float u_pixel = (pixel_col + pcg.random_float()) / samples_per_side;
              float v_pixel = (pixel_row + pcg.random_float()) / samples_per_side;
              Ray ray = fire_ray(col, row, u_pixel, v_pixel);
              cum_color = cum_color + func(ray); 
            }
          }
          image.set_pixel(col, row, cum_color * (1 / pow(samples_per_side,2)));

        } else {
          Ray ray = fire_ray(col, row);
          Color color = func(ray);
          image.set_pixel(col, row, color);
        }
      }
    }
  }

  
};

#endif
