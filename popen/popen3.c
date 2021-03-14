#include "popen3.h"
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clean_pair(int fd_pair[2]) {
  close(fd_pair[0]);
  close(fd_pair[1]);
}

stdpipes popen3(const char *cmd) {
  stdpipes result = {.out = NULL, .err = NULL, .in = NULL};

  int sin_pair[2];
  int sout_pair[2];
  int serr_pair[2];
  pid_t pid;

  if (pipe(sout_pair) < 0) {
    return result;
  }
  if (pipe(serr_pair) < 0) {
    clean_pair(sout_pair);
    return result;
  }
  if (pipe(sin_pair) < 0) {
    clean_pair(serr_pair);
    clean_pair(sout_pair);
    return result;
  }

  pid = vfork();

  if (pid < 0) {
    // Abort!
    clean_pair(sout_pair);
    clean_pair(serr_pair);
    clean_pair(sin_pair);
    return result;
  }

  if (pid == 0) {
    // I'm the child
    dup2(sout_pair[1], STDOUT_FILENO);
    clean_pair(sout_pair);

    dup2(serr_pair[1], STDERR_FILENO);
    clean_pair(serr_pair);

    dup2(sin_pair[0], STDIN_FILENO);
    clean_pair(sin_pair);

    execl("/bin/sh", "sh", "-c", cmd, NULL);
    exit(127);
  }

  result.out = fdopen(sout_pair[0], "r");
  close(sout_pair[1]);

  result.err = fdopen(serr_pair[0], "r");
  close(serr_pair[1]);

  result.in = fdopen(sin_pair[1], "w");
  close(sin_pair[0]);

  return result;
}
