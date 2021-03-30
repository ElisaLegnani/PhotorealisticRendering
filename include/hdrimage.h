#include "colors.h"
#include <cstdint> // It contains uint8_t
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

#ifndef _hdrimage_h_
#define _hdrimage_h_

enum class Endianness { little_endian, big_endian };

class InvalidPfmFileFormat: public exception{

private:
  string error_message;

public:
  explicit InvalidPfmFileFormat(const string& message): error_message(message){}

  const char* what() const noexcept override{
      return error_message.c_str();
    }
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

string read_line(stringstream &stream){ //da riscrivere per istream?
  string result = "";
  if(result!="\n"){
    stream >> result;
  }
  return result;
}
/*
def _read_float(stream, endianness=Endianness.LITTLE_ENDIAN):
    format_str = _FLOAT_STRUCT_FORMAT[endianness]

    try:
        return struct.unpack(format_str, stream.read(4))[0]
        
    except struct.error:
        # Capture the exception and convert it in a more appropriate type
        raise InvalidPfmFileFormat("impossible to read binary data from the file")


def _parse_endianness(line: str):
    try:
        value = float(line)
    except ValueError:
        raise InvalidPfmFileFormat("missing endianness specification")

    if value == 1.0:
        return Endianness.BIG_ENDIAN
    elif value == -1.0:
        return Endianness.LITTLE_ENDIAN
    else:
        raise InvalidPfmFileFormat("invalid endianness specification")

def _parse_img_size(line: str):
    elements = line.split(" ")
    if len(elements) != 2:
        raise InvalidPfmFileFormat("invalid image size specification")

    try:
        width, height = (int(elements[0]), int(elements[1]))
        if (width < 0) or (height < 0):
            raise ValueError()
    except ValueError:
        raise InvalidPfmFileFormat("invalid width/height")

    return width, height
}*/

class HdrImage { // Reminder: 1. width 2. height

private:
  void read_pfm(stringstream &stream){

    string magic = read_line(stream);
    if(magic!="PF"){
      throw InvalidPfmFileFormat("invalid magic in PFM file");
    }

    string img_size = read_line(stream);
    /*width, height = parse_img_size(img_size);

    endianness_line = read_line(stream);
    endianness = parse_endianness(endianness_line);

    result = HdrImage(width=width, height=height)
    for y in range(height - 1, -1, -1):
        for x in range(width):
            (r, g, b) = [_read_float(stream, endianness) for i in range(3)]
            result.set_pixel(x, y, Color(r, g, b))

    return result

  */

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
                Endianness endianness) { // scrivere anche save_pfm che scriva su file (ofstream)?

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
};

#endif
