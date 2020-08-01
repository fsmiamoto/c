#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// To test this, make a named pipe with the command `mkfifo`
// $ mkfifo mynamedpipe

// You can write to the named pipe using simple redirection
// cat whatever.txt > mynamedpipe
// This blocks until another process reads from the pipe.

int main() {
  // This is a blocking operation, the process waits until some other program
  // writes in the the named pipe.
  int fd = open("mynamedpipe", O_RDONLY);

  char c;

  while (read(fd, &c, 1) > 0) {
    printf("%c", c);
  }

  close(fd);
}
