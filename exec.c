#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid == 0) {
    printf("Hey I'm a new born with pid %d\n", getpid());
    execlp("ls", "-l", NULL);
  } else {
    printf("Waiting for my child %d\n", pid);
    int child_status;
    wait(&child_status);
    printf("My child exited with status %d\n", child_status);
  }
}
