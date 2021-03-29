#include "colors.h"
#include <cstdint> // It contains uint8_t
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

enum class Endianness { little_endian, big_endian };

void write_float(std::stringstream &stream, float value,
                 Endianness endianness) {

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

class HdrImage {  // Reminder: 1. width 2. height
                  // Written in little endian

private:
  void read_pfm(istream &stream);

public:
  int width;
  int height;
  string endianness = "-1.0";
  vector<Color> pixels;

  HdrImage(){};

  HdrImage(int w, int h) {
    width = w;
    height = h;
    pixels.resize(width * height);
  }

  HdrImage(ifstream &stream) { read_pfm(stream); }

  HdrImage(const string &filename) { 
    ifstream stream{filename};
    read_pfm(stream);
  }

  ~HdrImage(){};

  bool valid_coordinates(int x, int y) {
    return ((x >= 0) && (x < width) && (y >= 0) && (y < height));
  }

  int pixel_offset(int x, int y) { return y * width + x; }

  Color get_pixel(int x, int y) {
    if (valid_coordinates(x, y)) {
      return pixels[pixel_offset(x, y)];
    } else {
      abort();
    }
  }

  void set_pixel(int x, int y, Color new_color) {
    if (valid_coordinates(x, y)) {
      pixels[pixel_offset(x, y)] = new_color;
    } else {
      abort();
    }
  }

  void save_pfm(stringstream &sstr) { // scrivere anche save_pfm che scriva su file (ofstream)

    sstr << "PF\n" << width << " " << height << "\n" << endianness << "\n";

    for (int y{height - 1}; y >= 0; --y) {
      for (int x{}; x < width; ++x) {
        Color color = get_pixel(x, y);
        write_float(sstr, color.r, Endianness::little_endian);
        write_float(sstr, color.g, Endianness::little_endian);
        write_float(sstr, color.b, Endianness::little_endian);
      }
    }
  }

};


#endif
