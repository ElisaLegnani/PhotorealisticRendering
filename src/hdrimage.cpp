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
#include "functions.h"
#include <iostream>

using namespace std;

void write_float(ostream &stream, float value, Endianness endianness) {

  // Convert "value" in a sequence of 32 bit
  uint32_t double_word{*((uint32_t *)&value)};

  // Extract the four bytes in "double_word" using bit-level operators
  uint8_t bytes[] = {
      static_cast<uint8_t>(double_word & 0xFF), // Least significant byte
      static_cast<uint8_t>((double_word >> 8) & 0xFF),
      static_cast<uint8_t>((double_word >> 16) & 0xFF),
      static_cast<uint8_t>((double_word >> 24) & 0xFF), // Most significant byte
  };

  switch (endianness) {
  case Endianness::little_endian:
    for (int i{}; i < 4; ++i) // Forward loop
      stream << bytes[i];
    break;

  case Endianness::big_endian:
    for (int i{3}; i >= 0; --i) // Backward loop
      stream << bytes[i];
    break;
  }
}

float read_float(istream &stream, Endianness endianness) {

  float result;

  unsigned char bytes[4];

  for (int i{}; i<4; ++i)
    stream >> noskipws >> bytes[i];

  switch (endianness) {
  case Endianness::little_endian:
    memcpy(&result, &bytes, sizeof(result));
    break;

  case Endianness::big_endian:
    reverse(begin(bytes), end(bytes));
    memcpy(&result, &bytes, sizeof(result));
    break;
  }

  return result;
}

Endianness parse_endianness(string line) {
  float endianness;
  try {
    endianness = stof(line);
  } catch (invalid_argument) {
    throw InvalidPfmFileFormat("missing endianness specification");
  }

  if (endianness == -1.0) {
    return Endianness::little_endian;
  } else if (endianness == 1.0) {
    return Endianness::big_endian;
  } else {
    throw InvalidPfmFileFormat("invalid endianness specification");
  }
}

vector<int> parse_img_size(string line) {
  string delimiter = " ";
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<int> result;

  try {
    while ((pos_end = line.find(delimiter, pos_start)) != string::npos) {
      token = line.substr(pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      int token_int = stof(token);
      result.push_back(token_int);
    }

    result.push_back(stof(line.substr(pos_start)));

    if (result.size() != 2) {
      throw InvalidPfmFileFormat("Error: invalid image size specification.");
    }

    if (result[0] < 0 || result[1] < 0) {
      throw InvalidPfmFileFormat("Error: invalid width/height.");
    }

  } catch (invalid_argument) {
    throw InvalidPfmFileFormat("Error: invalid width/height.");
  }

  return result;
}

float clamp(float x) { return x / (1 + x); }

void HdrImage::read_pfm(istream &stream) {
  
  if(!stream){
        throw runtime_error("Error: HDR image does not exit.");
    }
  
  string magic;
  getline(stream, magic);
  if (magic != "PF") {
    throw InvalidPfmFileFormat("Error: invalid magic in PFM file.");
  }

  string img_size;
  getline(stream, img_size);
  vector<int> size = parse_img_size(img_size);

  string endianness_line;
  getline(stream, endianness_line);
  Endianness endianness = parse_endianness(endianness_line);

  width = size[0];
  height = size[1];
  pixels.resize(width * height);

  float rgb[3];

  for (int y{height - 1}; y >= 0; --y) {
    for (int x{}; x < width; ++x) {
      for (int i{}; i < 3; ++i) {
        rgb[i] = read_float(stream, endianness);
      }
      pixels[y * width + x] = Color(rgb[0], rgb[1], rgb[2]);
    }
  }
}

bool HdrImage::valid_coordinates(int x, int y) {
  return ((x >= 0) && (x < width) && (y >= 0) && (y < height));
}

int HdrImage::pixel_offset(int x, int y) { return y * width + x; }

Color HdrImage::get_pixel(int x, int y) {
  if (valid_coordinates(x, y)) {
    return pixels[pixel_offset(x, y)];
  } else {
    abort();
  }
}

void HdrImage::set_pixel(int x, int y, Color new_color) {
  if (valid_coordinates(x, y)) {
    pixels[pixel_offset(x, y)] = new_color;
  } else {
    abort();
  }
}

void HdrImage::save_pfm(ostream &stream, Endianness endianness = Endianness::little_endian) {
  string endianness_str;
  if (endianness == Endianness::little_endian) {
    endianness_str = "-1.0";
  } else if (endianness == Endianness::big_endian) {
    endianness_str = "1.0";
  }

  stream << "PF\n" << width << " " << height << "\n" << endianness_str << "\n";

  for (int y{height - 1}; y >= 0; --y) {
    for (int x{}; x < width; ++x) {
      Color color = get_pixel(x, y);
      write_float(stream, color.r, endianness);
      write_float(stream, color.g, endianness);
      write_float(stream, color.b, endianness);
    }
  }
}

float HdrImage::average_luminosity(float delta = 1e-10) {
  float cum_sum = 0.0;
  for (int i{}; i < pixels.size(); ++i) {
    cum_sum += log10(delta + pixels[i].luminosity());
  }
  return pow(10, cum_sum / pixels.size());
}

void HdrImage::normalize_image(float a) {
  float ave_lum = average_luminosity(1e-10);
  for (int i = 0; i < pixels.size(); i++) {
    pixels[i] = pixels[i] * (a / ave_lum);
  }
}

void HdrImage::normalize_image(float a, float luminosity) {
  for (int i = 0; i < pixels.size(); i++) {
    pixels[i] = pixels[i] * (a / luminosity);
  }
}

void HdrImage::clamp_image() {
  for (int i = 0; i < pixels.size(); i++) {
    pixels[i].r = clamp(pixels[i].r);
    pixels[i].g = clamp(pixels[i].g);
    pixels[i].b = clamp(pixels[i].b);
  }
}

void HdrImage::write_ldr_image(const string &filename, float gamma = 1.) {
  gdImagePtr img;
  FILE *f;

  // "True color" is the old name for 24-bit RGB images
  img = gdImageCreateTrueColor(width, height);

  for (int row{}; row < height; ++row) {
    for (int col{}; col < width; ++col) {
      int red, green, blue;
      Color c = get_pixel(col, row);
      
      if(c.r < 0 or c.r > 1 or c.g < 0 or c.g > 1 or c.b < 0 or c.b > 1){
        cerr << "Error: you need to apply the tone mapping before trying to generate a LDR image. Use normalise_image() and clamp_image() methods." << endl;
        abort();
      }
      
      red = int (255 * pow(c.r, 1/gamma));
      green = int (255 * pow(c.g, 1/gamma));
      blue = int (255 * pow(c.b, 1/gamma));;      
      gdImageSetPixel(img, col, row, gdImageColorExact(img, red, green, blue));
    }
  }

  const char* file = filename.c_str();
  f = fopen(file, "wb");

  string format = get_format(string(filename));

  // Output the image to the disk file in PNG format
  if(format==".png"){
    gdImagePng(img, f);
  } else if (format == ".jpg"){
    gdImageJpeg(img, f, -1);
  }

  fclose(f);
  gdImageDestroy(img);

}
