#include "colors.h"
#include <cstdlib>

int main() {

  Color c1(1.0, 2.0, 3.0);
  Color c2(5.0, 7.0, 9.0);

  return (c1 * c2).is_color_close(Color{5.0, 14.0, 27.0}) ? EXIT_SUCCESS
                                                          : EXIT_FAILURE;
}