#include <stdio.h>
#include <unistd.h>

// Move the the location of the progrm break using sbrk;
// man brk

int main() {
  void *first = sbrk(0);
  void *second = sbrk(4096);
  void *third = sbrk(0);

  // Not good...
  int *ptr = (int *)third + 10;
  *ptr = 0xDEAD;

  printf("First: %p\n", first);
  printf("Second: %p\n", second);
  printf("Third: %p\n", third);
}
