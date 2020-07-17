#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *myturn(void *arg) {
  for (int i = 0; i < 8; i++) {
    sleep(1);
    printf("My turn!\n");
  }

  return NULL;
}

void yourturn() {
  for (int i = 0; i < 3; i++) {
    sleep(2);
    printf("Your turn!\n");
  }
}

int main() {
  pthread_t newthread;
  pthread_create(&newthread, NULL, myturn, NULL);

  yourturn();

  // Wait for the other thread to finish
  pthread_join(newthread, NULL);
}
