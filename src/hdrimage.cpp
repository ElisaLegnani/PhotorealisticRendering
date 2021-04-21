#include "hdrimage.h"

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

string read_line(istream &stream) {
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
    istream &stream,
    Endianness endianness) { // da implementare endianness e exception

  float result;
  stream.read(reinterpret_cast<char *>(&result), sizeof(float));

  return result;
}

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

float clamp(float x) { return x / (1 + x); }

void HdrImage::read_pfm(istream &stream) {

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

void HdrImage::save_pfm(ostream &sstr, Endianness endianness) {
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

float HdrImage::average_luminosity(float delta) {
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