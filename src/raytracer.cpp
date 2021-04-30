#include "colors.h"
#include "hdrimage.h"
#include <iostream>
#include <gd.h>
/*#include <stdio.h>*/

using namespace std;

int main(int argc, char *argv[]) {

  string pfm_filename;
  string out_filename;
  float a, gamma;

  if (argv[1] == NULL) {
    cout << "Insert input PFM filename: ";
    cin >> pfm_filename;
    cout << "Insert a: ";
    cin >> a;
    cout << "Insert gamma: ";
    cin >> gamma;
    cout << "Insert output PNG/JPG filename: ";
    cin >> out_filename;
  } else {
    pfm_filename = argv[1];
    a = atof(argv[2]);
    gamma = atof(argv[3]);
    out_filename = argv[4];
  }

  HdrImage img(pfm_filename);

  img.normalize_image(a);
  img.clamp_image();

  img.write_ldr_image(out_filename, gamma);

  return 0;
}
