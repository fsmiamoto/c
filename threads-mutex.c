#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#define BIG 100000000UL
uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void count_to_big() {
  for (uint32_t i = 0; i < BIG; i++) {
    counter++;
  }
}

void *count_to_big_thread_safe(void *arg) {
  // To avoid race conditions, we need to use a mutex
  // but in this case the overhead is so large that it's
  // just isn't worth it
  for (uint32_t i = 0; i < BIG; i++) {
    pthread_mutex_lock(&lock);
    counter++;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main() {
  count_to_big();
  count_to_big();
  printf("Done. Counter = %u \n", counter);

  // Create a thread so we have to concurrent count_to_big functions running
  counter = 0;
  printf("Now with threads...\n");

  pthread_t t;
  pthread_create(&t, NULL, count_to_big_thread_safe, NULL);
  count_to_big_thread_safe(NULL);

  pthread_join(t, NULL);

  printf("Done. Counter = %u \n", counter);
}
