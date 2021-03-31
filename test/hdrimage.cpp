#include "hdrimage.h"
#include "colors.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {

  HdrImage img(7, 4);

  if (img.width != 7 || img.height != 4) {
    abort();
  }

  if (img.valid_coordinates(0, 0) == 0 || img.valid_coordinates(6, 3) == 0 ||
      img.valid_coordinates(-1, 0) != 0 || img.valid_coordinates(0, -1) != 0) {
    abort();
  }

  if (img.pixel_offset(0, 0) != 0 || img.pixel_offset(3, 2) != 17 ||
      img.pixel_offset(6, 3) != (7 * 4 - 1)) {
    abort();
  }

  Color reference_color = Color(1.0, 2.0, 3.0);
  img.set_pixel(3, 2, reference_color);

  if (img.get_pixel(3, 2).is_color_close(reference_color) == 0) {
    abort();
  }

  // Test save_pfm

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

  stringstream sstr;
  img2.save_pfm(sstr, Endianness::little_endian);

  string ref_string(reference_bytes,
                    reference_bytes +
                        sizeof(reference_bytes) / sizeof(reference_bytes[0]));

  if (sstr.str() != ref_string) {
    abort();
  }

  // Test pfm_read_line

  stringstream sstr2;
  sstr2 << "hello,\nworld";

  if (read_line(sstr2) != "hello," || read_line(sstr2) != "world" ||
      read_line(sstr2) != "") {
    abort();
  }

  // Test pfm_pase_img_size

  vector<int> ref_img_size = {3, 2};

  if (parse_img_size("3 2") != ref_img_size) {
    abort();
  }

  // Test read_pfm

  HdrImage img3(sstr);
  if (img3.width != 3 || img3.height != 2) {
    abort();
  }
  if (img3.get_pixel(0, 0).is_color_close(Color(1.0e1, 2.0e1, 3.0e1)) == 0 ||
      img3.get_pixel(2, 1).is_color_close(Color(7.0e2, 8.0e2, 9.0e2)) == 0) {
    abort();
  }

  // Test average_luminosity

  HdrImage img4(2, 1);

  img4.set_pixel(0, 0, Color(5.0, 10.0, 15.0));
  img4.set_pixel(1, 0, Color(500.0, 1000.0, 1500.0));

  if ((img4.average_luminosity(0.0) == 100) == 0) {
    abort();
  }

  //  Test normalize_image

  img4.normalize_image(1000.0, 100.0);

  if (img4.get_pixel(0, 0).is_color_close(Color(0.5e2, 1.0e2, 1.5e2)) == 0 ||
      img4.get_pixel(1, 0).is_color_close(Color(0.5e4, 1.0e4, 1.5e4)) == 0) {
    abort();
  }

  return 0;
}
