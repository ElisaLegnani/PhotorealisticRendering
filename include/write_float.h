
#include <cstdint> // It contains uint8_t
#include <iostream>
#include <sstream>
#include <string>

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

// How to use little/big endian-encoded floats:
// write_float(stream, 10.0, Endianness::little_endian);
// write_float(stream, 10.0, Endianness::big_endian);
