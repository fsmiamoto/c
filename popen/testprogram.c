#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096

int main(int argc, char **argv) {

  fprintf(stdout, "stdout: Hello there\n");
  char buffer[BUFSIZE];

  while (fgets(buffer, BUFSIZE, stdin)) {
    fprintf(stdout, "stdin: %s\n", buffer);
  }

  fprintf(stderr, "stderr: errrooou\n");
  return EXIT_SUCCESS;
}
