#include "colors.h"
#include <gd.h> /* The library's header file */
#include "hdrimage.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  string pfm_filename;
  char* png_filename;
  float a, gamma;

  if (argv[1] == NULL) {
    cout << "Insert input PFM filename: ";
    cin >> pfm_filename;
    cout << "Insert a: ";
    cin >> a;
    cout << "Insert gamma: ";
    cin >> gamma;
    cout << "Insert output PNG filename: ";
    cin >> png_filename;
  } else {
    pfm_filename = argv[1];
    a = atof(argv[2]);
    gamma = atof(argv[3]);
    png_filename = argv[4];
  }

  // const int width = 256, height = 256;
  gdImagePtr im;
  FILE *f;
  int row, col;

  HdrImage img(pfm_filename);

  const int width = img.width, height = img.height;

  // "True color" is the old name for 24-bit RGB images
  im = gdImageCreateTrueColor(width, height);

  img.normalize_image(a);
  img.clamp_image();

  for (row = 0; row < height; ++row) {
    for (col = 0; col < width; ++col) {
      float red, green, blue;
      Color c = img.get_pixel(col, row);
      red = c.r;
      green = c.g;
      blue = c.b;

      red = (int)(red * 255.0);
      green = (int)(green * 255.0);
      blue = (int)(blue * 255.0);
      
      gdImageSetPixel(im, col, row, gdImageColorExact(im, red, green, blue));
    }
  }

  f = fopen(png_filename, "wb");

  /* Output the image to the disk file in PNG format. */
  gdImagePng(im, f); /* gdImageJpeg(im, jpegout, -1); */

  fclose(f);
  gdImageDestroy(im);

  cout << "PNG image ready!" << endl;

  return 0;
}
