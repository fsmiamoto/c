#include <assert.h>
#include <stdio.h>

// You can remove the assertions compiling with some directives:
// gcc -DNDEBUG assertions.c
// Nice...

void do_some_stuff(int **p) { *p = NULL; }

int main() {
  int x = 25;
  int *ptr = &x;

  // All good
  assert(ptr != NULL);

  do_some_stuff(&ptr);

  // Oops...
  assert(ptr != NULL);
}
