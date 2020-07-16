#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Not all functions from are safe to be called from a signal handler
// https://man7.org/linux/man-pages/man7/signal-safety.7.html
void handler(int num) { write(STDOUT_FILENO, "I won't die!\n", 20); }

int main() {
  signal(SIGINT, handler);
  signal(SIGTERM, handler);

  while (1) {
    printf("Wasting your cycles. %d\n", getpid());
    sleep(1);
  }
}
