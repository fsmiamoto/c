#include <stdio.h>
#include <unistd.h>

#define BIG 10000000L
#define DIVIDER 500

void do_some_stuff(int niceval) {
  nice(niceval);

  for (long i = 0; i < BIG; i++)
    if (i % (BIG / DIVIDER) == 0)
      printf("p=%d ---> %ld\n", niceval, i);
}

int main() {
  if (fork() == 0)
    do_some_stuff(1);
  else
    do_some_stuff(2);
}
