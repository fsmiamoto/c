#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(-1);
  }

  int fd;
  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    // Print the message related to the error number
    // The possibles errors are described in the man page for the syscall

    // The two lines below are equivalent
    fprintf(stderr, "error: %s\n", strerror(errno));
    perror("error");

    exit(-1);
  }

  char c;
  while (read(fd, &c, 1) > 0) {
    fputc(c, stdout);
  }

  close(fd);
}
