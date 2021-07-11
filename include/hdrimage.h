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

#ifndef _hdrimage_h_
#define _hdrimage_h_

#include "colors.h"
#include <fstream>
#include <string>
#include <vector>
#include <gd.h>
#include <cstring>
#include <algorithm>

enum class Endianness { little_endian, big_endian };

struct InvalidPfmFileFormat : public runtime_error {
  InvalidPfmFileFormat(const string &message): runtime_error(message) {}
};

void write_float(ostream &stream, float value, Endianness endianness);

float read_float(istream &stream, Endianness endianness);

Endianness parse_endianness(string line);

vector<int> parse_img_size(string line);

float clamp(float x);

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
