#include <stdio.h>
#include <stdlib.h>

int main() {
  char *home = getenv("HOME");
  char *user = getenv("USER");

  printf("I'm %s and my home dir is at %s\n", user, home);

  char *password = getenv("PASSWORD"); // not defined
  printf("Oops PASSWORD isn't set: %s\n", password);
}
