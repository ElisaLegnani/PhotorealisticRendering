#include "colors.h"
#include <cstdint> // It contains uint8_t
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

enum class Endianness { little_endian, big_endian };

class InvalidPfmFileFormat : public exception {

private:
  string error_message;

public:
  explicit InvalidPfmFileFormat(const string &message)
      : error_message(message) {}

  const char *what() const noexcept override { return error_message.c_str(); }
};

void write_float(ostream &stream, float value, Endianness endianness);

string read_line(istream &stream);

float read_float(
    istream &stream,
    Endianness endianness); // da implementare endianness e exception

// implementare parse_endianness(string line);

vector<int> parse_img_size(string line);

float clamp(float x);

class HdrImage { // Reminder: 1. width 2. height

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

  void save_pfm(ostream &sstr, Endianness endianness);

  float average_luminosity(float delta);
  void normalize_image(float a);
  void normalize_image(float a, float luminosity);
  void clamp_image();
};

#endif