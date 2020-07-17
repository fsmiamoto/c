#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

void hard_work() { usleep(1500); }

int main() {
  // Using time, only seconds resolution, not very good...
  long before = time(NULL);
  hard_work();
  long after = time(NULL);

  printf("%ld elapsed seconds\n", after - before);

  // With clock, you can get a better resolution
  before = clock();
  hard_work();
  after = clock();

  double elapsed = (double)(after - before) / CLOCKS_PER_SEC;
  printf("%lf seconds elapsed\n", elapsed);

  // Using the tms struct

  clock_t resolution = sysconf(_SC_CLK_TCK);

  struct tms before_s;
  times(&before_s);
  hard_work();
  struct tms after_s;
  times(&after_s);

  elapsed = (double)(after_s.tms_utime - before_s.tms_utime);
  printf("%lf seconds elapsed\n", elapsed);
}
