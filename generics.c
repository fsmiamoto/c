// Source: https://embeddedbits.org/gcc-extensions-to-the-c-language/
#include <stdio.h>

#define max(a, b)                                                              \
  ({                                                                           \
    typeof(a) _a = (a);                                                        \
    typeof(b) _b = (b);                                                        \
    _a > _b ? _a : _b;                                                         \
  })

int main(int argc, const char *argv[]) {
  int x = 1024, y = 4096;
  char a = 10, b = 20;
  float j = 1.0, k = 2.0;

  printf("char  max is %d\n", max(a, b));
  printf("int   max is %d\n", max(x, y));
  printf("float max is %f\n", max(j, k));

  return 0;
}
