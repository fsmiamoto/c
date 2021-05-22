#include <stdio.h>
#include <stdlib.h>

// Run it like this: echo 'the stack is going to get smashed' | ./a.out
int main() {
  char stack_string[6] = "stack";
  int x = 10;

  printf("Enter a string for the stack: ");
  // Never use gets
  gets(stack_string);

  printf("Stack string is: %s\n", stack_string);
  printf("x is: %d\n", x);
}
