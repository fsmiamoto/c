#include <stdio.h>
#include <string.h>

#define BUFLEN 64

int main() {
  char input[BUFLEN] = "Rey, Luke, Leia: Anakin, Padme";
  int i = 0;

  char *token = strtok(input, "-");
  printf("%d: [%p] --- %s\n", i, token, token);

  // Get the first element
  token = strtok(input, ",:");
  printf("%d: [%p] --- %s\n", i, token, token);

  while (token != NULL) {
    // Pick up wehre the last call left off by passing NULL
    token = strtok(NULL, ",:");
    printf("%d: [%p] --- %s\n", i, token, token);
  }

  // strtok change the original string!
  printf("%s\n", input); // Rey\n

  // Since it uses a static variable to keep track of where it is,
  // strtok is not thread safe. See strtok_r for a alternative.
}
