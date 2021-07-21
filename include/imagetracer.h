/* 
Copyright (C) 2021 Adele Zaini, Elisa Legnani

This file is part of PhotorealisticRendering.

PhotorealisticRendering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PhotorealisticRendering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
