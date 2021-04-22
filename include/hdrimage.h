#ifndef _hdrimage_h_
#define _hdrimage_h_

#include "colors.h"
#include <vector>
#include <string>
#include <fstream>

enum class Endianness { little_endian, big_endian };

class InvalidPfmFileFormat : public runtime_error {
public:
  explicit InvalidPfmFileFormat(const string &message) noexcept : runtime_error(message) {}
};

void write_float(ostream &stream, float value, Endianness endianness);

string read_line(istream &stream);

float read_float(
    istream &stream,
    Endianness endianness); // da implementare endianness e exception

// implementare parse_endianness(string line);

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
};

#endif
