#include "colors.h"
#include <cstdlib>

int main() {

  Color c1(1.0, 2.0, 3.0);
  Color c2(5.0, 7.0, 9.0);

  // Color c3 = c3.sum_colors(c1,c2);

  return c1.are_colors_close(Color{1.0, 2.0, 3.0}, c1) ? EXIT_SUCCESS
                                                        : EXIT_FAILURE;
}