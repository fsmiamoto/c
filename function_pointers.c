#include <stdio.h>
#include <stdlib.h>

typedef int (*op_func)(int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int do_operation(op_func op, int x, int y) { return op(x, y); }

int main(int argc, char **argv) {
  int result = do_operation(add, 2, 2);
  int result2 = do_operation(sub, 2, 2);

  printf("Result 1: %d", result);
  printf("Result 2: %d\n", result2);
}
