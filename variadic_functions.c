#include <stdarg.h>
#include <stdio.h>

void print_ints(int num, ...) {
  va_list args;

  va_start(args, num);

  for (int i = 0; i < num; i++) {
    int value = va_arg(args, int);
    printf("%d: %d\n", i, value);
  }

  va_end(args);
}

int my_printf(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  int done = vfprintf(stdout, fmt, args);
  va_end(args);

  return done;
}

int main() {
  print_ints(5, 1, 2, 3, 4, 5);
  my_printf("%s %s %s\n", "Hey", "Ho", "Let's go");
}
