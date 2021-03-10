#include "colors.h"
#include <cstdlib>

int main() {

  Color c1(1.0, 2.0, 3.0);
  Color c2(5.0, 7.0, 9.0);

  return c1.are_colors_close(Color{4.0, 5.0, 6.0}, c2 - c1) ? EXIT_SUCCESS
                                                            : EXIT_FAILURE;
}