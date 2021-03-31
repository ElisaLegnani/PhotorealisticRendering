#include "colors.h"
#include "hdrimage.h"
#include "gd.h"     /* The library's header file */
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  if (argv[1] == NULL)
    cout << "Hello, World!" << endl;
  else
    cout << "Hello, " << argv[1] << "!" << endl;


  //const int width = 256, height = 256;
  gdImagePtr im;
  FILE *f;
  int row, col;

  HdrImage img2("memorial.pfm");

  const int width = img2.width, height = img2.height;  

  // "True color" is the old name for 24-bit RGB images
  im = gdImageCreateTrueColor(width, height);

  img2.normalize_image(10000.0, 100.0);
  //img2.clamp_image();

  for(row = 0; row < height; ++row) {
    for(col = 0; col < width; ++col) {
      int red, green, blue;
      Color c = img2.get_pixel(col, row);
      red = c.r;
      green = c.g;
      blue = c.b;

      //red = (int) (col * 255.0 / width);
      //green = (int) ((1.0 - row * 1.0 / height) * 255.0);
      gdImageSetPixel(im, col, row, gdImageColorExact(im, red, green, blue));
    }
  }

  f = fopen("image.png", "wb");

  /* Output the image to the disk file in PNG format. */
  gdImagePng(im, f);  /* gdImageJpeg(im, jpegout, -1); */

  fclose(f);
  gdImageDestroy(im);


  return 0;
}