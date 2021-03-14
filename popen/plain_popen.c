#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096

int main() {
  FILE *pipe = popen("echo 'Some text' | ./testprogram", "r");

  char buffer[BUFSIZE];
  while (fgets(buffer, BUFSIZE, pipe)) {
    printf("testprogram: %s", buffer);
  }
  pclose(pipe);
}
