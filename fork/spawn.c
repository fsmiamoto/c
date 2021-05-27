#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// external symbol that always points to the list of environment variables
extern char **environ;

int main(int argc, char **argv) {
  char *args[4] = {"/bin/echo", "hello", "world", 0};
  int child_status;
  int result;

  if (posix_spawn(&result, args[0], NULL, NULL, args, environ) != 0) {
    perror("spawn failed");
    exit(1);
  }
  wait(&child_status);
  printf("child exited with status: %d\n", child_status);
}
