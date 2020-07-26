#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TERMS_PER_THREAD NUM_OF_TERMS / NUM_OF_THREADS

// NUM_OF_THREADS and NUM_OF_TERMS are defined externally, see Makefile
double results[NUM_OF_THREADS];

void *pi_thread(void *index) {
  long i = (long)index;

  double from = i * TERMS_PER_THREAD;
  double to = from + TERMS_PER_THREAD;

  double result;
  for (result = 0; from < to; from++) {
    result += pow(-1.0, from) / (2 * from + 1);
  }

  results[i] = result * 4;
  return 0;
}

int main(int argc, char **argv) {
  pthread_t threads[NUM_OF_THREADS];
  pthread_attr_t attr;

  long i, status;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (i = 0; i < NUM_OF_THREADS; i++) {
    status = pthread_create(&threads[i], &attr, pi_thread, (void *)i);
    if (status < 0) {
      perror("pthread_create");
      exit(1);
    }
  }

  double pi;
  for (i = 0; i < NUM_OF_THREADS; i++) {
    printf("Main: aguardando thread %02ld\n", i);
    status = pthread_join(threads[i], NULL);
    if (status < 0) {
      perror("pthread_join");
      exit(1);
    }
    pi += results[i];
  }

  printf("Pi: %.20lf\n", pi);
}
