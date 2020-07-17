#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Don't forget the -lpthread flag for compiling!

// Recieve an argument and return a result
void *myturn(void *arg) {
  // Typecast the generic pointer
  int *turns = (int *)arg;

  for (int i = 0; i < *turns; i++) {
    sleep(1);
    printf("My turn! %d\n", i);
  }

  int *result = (int *)malloc(sizeof(int));
  *result = 42;

  return result;
}

void your_turn(int turns) {
  for (int i = 0; i < turns; i++) {
    sleep(2);
    printf("Your turn! %d\n", i);
  }
}

int main() {
  pthread_t t;

  int turns = 8;
  pthread_create(&t, NULL, myturn, &turns);

  your_turn(5);

  int *result;
  pthread_join(t, (void **)&result);

  printf("Result from thread: %d\n", *result);

  // Clean it up
  free(result);
}
