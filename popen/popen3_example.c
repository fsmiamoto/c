#include "./popen3.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096

int main() {
  stdpipes pipes = popen3("./testprogram");
  char buffer[BUFSIZE];

  fprintf(pipes.in, "Hello from popen3\n");
  fclose(pipes.in);

  while (fgets(buffer, BUFSIZE, pipes.out)) {
    printf("testprogram: %s", buffer);
  }

  while (fgets(buffer, BUFSIZE, pipes.err)) {
    printf("testprogram(err): %s", buffer);
  }

  fclose(pipes.out);
  fclose(pipes.err);
}
