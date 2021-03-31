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

string read_line(stringstream &stream) { // da riscrivere per istream?
  string result = "";
  string r = "";
  while (stream && r != "\n") {
    r = stream.get();
    if (r == "\n" || !stream) {
      break;
    }
    result.append(r);
  }
  return result;
}

float read_float(
    stringstream &stream,
    Endianness endianness) { // da implementare endianness e exception

  float result;
  stream.read(reinterpret_cast<char *>(&result), sizeof(float));

  return result;
}

// implementare parse_endianness(string line){}

vector<int> parse_img_size(string line) { // sistemare exceptions
  string delimiter = " ";
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<int> result;

  while ((pos_end = line.find(delimiter, pos_start)) != string::npos) {
    token = line.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    int token_int = stof(token);
    result.push_back(token_int);
  }

  result.push_back(stof(line.substr(pos_start)));

  if (result.size() != 2) {
    throw InvalidPfmFileFormat("invalid image size specification");
  }

  if (result[0] < 0 || result[1] < 0) {
    throw InvalidPfmFileFormat("invalid width/height");
  }

  return result;
}

class HdrImage { // Reminder: 1. width 2. height

private:
  void read_pfm(stringstream &stream) {

    string magic = read_line(stream);
    if (magic != "PF") {
      throw InvalidPfmFileFormat("invalid magic in PFM file");
    }

    string img_size = read_line(stream);
    vector<int> size = parse_img_size(img_size);

    string endianness_line = read_line(stream);
    // endianness = parse_endianness(endianness_line);

    width = size[0];
    height = size[1];
    pixels.resize(width * height);

    float rgb[3];

    for (int y{height - 1}; y >= 0; --y) {
      for (int x{}; x < width; ++x) {
        for (int i{}; i < 3; ++i) {
          rgb[i] = read_float(stream, Endianness::little_endian);
        }
        pixels[y * width + x] = Color(rgb[0], rgb[1], rgb[2]);
      }
    }
  }

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

  HdrImage(stringstream &stream) { read_pfm(stream); }

  HdrImage(const string &filename) {
    stringstream stream{filename};
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

  void save_pfm(stringstream &sstr,
                Endianness endianness) { // scrivere anche save_pfm che scriva
                                         // su file (ofstream)?

    string endianness_str;
    if (endianness == Endianness::little_endian) {
      endianness_str = "-1.0";
    } else if (endianness == Endianness::big_endian) {
      endianness_str = "1.0";
    }

    sstr << "PF\n" << width << " " << height << "\n" << endianness_str << "\n";

    for (int y{height - 1}; y >= 0; --y) {
      for (int x{}; x < width; ++x) {
        Color color = get_pixel(x, y);
        write_float(sstr, color.r, endianness);
        write_float(sstr, color.g, endianness);
        write_float(sstr, color.b, endianness);
      }
    }
  }

  float average_luminosity(float delta = 1e-10) {
    float cum_sum = 0.0;
    for (int i{}; i < pixels.size(); ++i) {
      cum_sum += log10(delta + pixels[i].luminosity());
    }

    return pow(10, cum_sum / pixels.size());
  }
};

#endif
