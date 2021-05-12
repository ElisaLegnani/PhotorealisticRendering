#include "hdrimage.h"
#include "catch_amalgamated.hpp"
#include <iostream>
#include <sstream>

#define CATCH_CONFIG_MAIN

using namespace std;

HdrImage img(7, 4);

TEST_CASE("Hdrimage constructor", "[hdrimage]") {
  REQUIRE(img.width == 7);
  REQUIRE(img.height == 4);
}

TEST_CASE("Hdrimage valid_coordinates", "[hdrimage]") {
  REQUIRE(img.valid_coordinates(0, 0));
  REQUIRE(img.valid_coordinates(6, 3));
  REQUIRE(!img.valid_coordinates(-1, 0));
  REQUIRE(!img.valid_coordinates(0, -1));
}

TEST_CASE("Hdrimage pixel_offset", "[hdrimage]") {
  REQUIRE(img.pixel_offset(0, 0) == 0);
  REQUIRE(img.pixel_offset(3, 2) == 17);
  REQUIRE(img.pixel_offset(6, 3) == (7 * 4 - 1));
}

TEST_CASE("Hdrimage get_pixel", "[hdrimage]") {

  Color reference_color = Color(1.0, 2.0, 3.0);
  img.set_pixel(3, 2, reference_color);

  REQUIRE(img.get_pixel(3, 2).is_color_close(reference_color));
}

// ––––––––––––––––– Test PFM methods  –––––––––––––––––

stringstream sstr;

TEST_CASE("Hdrimage save_pfm", "[hdrimage]") {

  HdrImage img2(3, 2);
  img2.set_pixel(0, 0, Color(1.0e1, 2.0e1, 3.0e1));
  img2.set_pixel(1, 0, Color(4.0e1, 5.0e1, 6.0e1));
  img2.set_pixel(2, 0, Color(7.0e1, 8.0e1, 9.0e1));
  img2.set_pixel(0, 1, Color(1.0e2, 2.0e2, 3.0e2));
  img2.set_pixel(1, 1, Color(4.0e2, 5.0e2, 6.0e2));
  img2.set_pixel(2, 1, Color(7.0e2, 8.0e2, 9.0e2));

  unsigned char reference_bytes[] = {
      0x50, 0x46, 0x0a, 0x33, 0x20, 0x32, 0x0a, 0x2d, 0x31, 0x2e, 0x30, 0x0a,
      0x00, 0x00, 0xc8, 0x42, 0x00, 0x00, 0x48, 0x43, 0x00, 0x00, 0x96, 0x43,
      0x00, 0x00, 0xc8, 0x43, 0x00, 0x00, 0xfa, 0x43, 0x00, 0x00, 0x16, 0x44,
      0x00, 0x00, 0x2f, 0x44, 0x00, 0x00, 0x48, 0x44, 0x00, 0x00, 0x61, 0x44,
      0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0xa0, 0x41, 0x00, 0x00, 0xf0, 0x41,
      0x00, 0x00, 0x20, 0x42, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x70, 0x42,
      0x00, 0x00, 0x8c, 0x42, 0x00, 0x00, 0xa0, 0x42, 0x00, 0x00, 0xb4, 0x42};

  img2.save_pfm(sstr, Endianness::little_endian);

  // conversione da unsigned char a string
  string ref_string(reference_bytes,
                    reference_bytes +
                        sizeof(reference_bytes) / sizeof(reference_bytes[0]));

  REQUIRE(sstr.str() == ref_string);
}

TEST_CASE("Hdrimage pfm_read_line", "[hdrimage]") {

  stringstream sstr2;
  sstr2 << "hello,\nworld";

  REQUIRE(read_line(sstr2) == "hello,");
  REQUIRE(read_line(sstr2) == "world");
  REQUIRE(read_line(sstr2) == "");
}

TEST_CASE("Hdrimage pfm_pase_img_size", "[hdrimage]") {

  vector<int> ref_img_size = {3, 2};

  REQUIRE(parse_img_size("3 2") == ref_img_size);
}

TEST_CASE("Hdrimage read_pfm", "[hdrimage]") {

  HdrImage img3(sstr);

  REQUIRE(img3.width == 3);
  REQUIRE(img3.height == 2);
  REQUIRE(img3.get_pixel(0, 0).is_color_close(Color(1.0e1, 2.0e1, 3.0e1)));
  REQUIRE(img3.get_pixel(2, 1).is_color_close(Color(7.0e2, 8.0e2, 9.0e2)));
}

// ––––––––––––––––– Test average_luminosity  –––––––––––––––––

HdrImage img4(2, 1);

TEST_CASE("Hdrimage average_luminosity", "[hdrimage]") {

  img4.set_pixel(0, 0, Color(5.0, 10.0, 15.0));
  img4.set_pixel(1, 0, Color(500.0, 1000.0, 1500.0));

  REQUIRE(img4.average_luminosity(0.0) == 100);
}

// ––––––––––––––––– Test normalize_image –––––––––––––––––

TEST_CASE("Hdrimage normalize_image", "[hdrimage]") {

  img4.normalize_image(1000.0, 100.0);

  REQUIRE(img4.get_pixel(0, 0).is_color_close(Color(0.5e2, 1.0e2, 1.5e2)));
  REQUIRE(img4.get_pixel(1, 0).is_color_close(Color(0.5e4, 1.0e4, 1.5e4)));
}

// ––––––––––––––––– Test clamp_image –––––––––––––––––

TEST_CASE("Hdrimage clamp_image", "[hdrimage]") {

  img4.set_pixel(0, 0, Color(0.5e1, 1.0e1, 1.5e1));
  img4.set_pixel(1, 0, Color(0.5e3, 1.0e3, 1.5e3));

  img4.clamp_image();

  // Just check that the R/G/B values are within the expected boundaries
  for (int i = 0; i < img4.pixels.size(); i++) {
    REQUIRE(img4.pixels[i].r > 0);
    REQUIRE(img4.pixels[i].r < 1);
    REQUIRE(img4.pixels[i].g > 0);
    REQUIRE(img4.pixels[i].g < 1);
    REQUIRE(img4.pixels[i].b > 0);
    REQUIRE(img4.pixels[i].b < 1);
  }
}
