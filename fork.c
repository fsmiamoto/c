#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid == 0) {
    printf("I'm a child\n");
  } else {
    printf("I'm the father of %d\n", pid);
  }
}
