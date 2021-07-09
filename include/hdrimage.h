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

#ifndef _hdrimage_h_
#define _hdrimage_h_

#include "colors.h"
#include <fstream>
#include <string>
#include <vector>
#include <gd.h>
#include <cstring>
#include <algorithm>


//–––––––––––––––––– Functions for HdrImage ––––––––––––––––––––––––––

/**
 * Order of reading bits in a byte.
 * The same sequence of bits (a byte) can be interpreted in two different ways if starting to read it from the most or from the least significant bit.
 
 * @param big_endian (BE) starts reading bits from the most significant to the least one (as reading from left to right)
 * @param little_endian (LE) starts reading bits from the least significant to the most one (as reading from right to left)
 */
enum class Endianness { little_endian, big_endian };

/**
 * Derived struct from runtime_error, defined to catch specific errors in reading PFM input files
 */
struct InvalidPfmFileFormat : public runtime_error {
  InvalidPfmFileFormat(const string &message): runtime_error(message) {}
};

/**
 * Write a floating-point number in the form of 4 bytes onto a stream, according to the given endianness
 *
 * @param stream where to push the bytes on
 * @param value to convert in bytes
 * @param endianness big/little endianness to write it in the proper order
 */
void write_float(ostream &stream, float value, Endianness endianness);

/**
 * Read bytes from a stream and return the interpreted floating point number, according to the given endianness
 *
 * @param stream where to read bytes
 * @param endianness big/little endianness to interpret bytes properly
 *
 * @return interpreted floating point number
 */
float read_float(istream &stream, Endianness endianness);

/**
 * Interpret a string in a floating-point number (1.0 or -1.0) and return the respective endianness
 *
 * @param line string to be interpreted as 1.0 or -1.0
 *
 * @return big_endianness if 1.0 or little_endianness if -1.0
 */
Endianness parse_endianness(string line);

/**
 * Interpret a string into the size of the image (width and height)
 *
 * @param line string to be interpreted as size
 *
 * @return vector of integers containing (width,height) of the image
 */
vector<int> parse_img_size(string line);

float clamp(float x);


//–––––––––––––––––– Class HdrImage ––––––––––––––––––––––––––––––––––
class HdrImage {

private:
  void read_pfm(istream &stream);

public:
  int width;
  int height;
  vector<Color> pixels;

  HdrImage(){};

  HdrImage(int w, int h) {
    width = w;
    height = h;
    pixels.resize(width * height);
  }

  HdrImage(istream &stream) { read_pfm(stream); }

  HdrImage(const string &filename) {
    ifstream stream{filename};
    read_pfm(stream);
  }

  ~HdrImage(){};

  bool valid_coordinates(int x, int y);
  int pixel_offset(int x, int y);
  Color get_pixel(int x, int y);
  void set_pixel(int x, int y, Color new_color);

  void save_pfm(ostream &stream, Endianness endianness);

  float average_luminosity(float delta);
  void normalize_image(float a);
  void normalize_image(float a, float luminosity);
  void clamp_image();
  void write_ldr_image(const string &filename, float gamma);

};

#endif
