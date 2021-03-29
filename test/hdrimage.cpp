#include "hdrimage.h"
#include "colors.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <sstream>

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
  img2.save_pfm(sstr);

  string ref_string(reference_bytes,
                    reference_bytes +
                        sizeof(reference_bytes) / sizeof(reference_bytes[0]));

  // cout << "Reference bytes" << endl << ref_string <<endl;
  // cout << "Stream bytes" << endl << sstr.str() <<endl;

  if (sstr.str() != ref_string) {
    abort();
  }

  return 0;
}
