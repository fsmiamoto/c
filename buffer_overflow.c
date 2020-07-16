#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 10

/*
    strcpy is unsafe!
    Run this program with
    $ ./a.out NewPassword 1234567890NewPassword

    The length of the message depends on how far apart are
    the buffer and password on the final binary.
    You can check those with something like objdump or xxd
*/

char buffer[BUFFERSIZE] = "message";
char password[BUFFERSIZE] = "passw0rd";

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("usage: %s <password> <string_to_print>\n", argv[0]);
    exit(1);
  }

  strcpy(buffer, argv[2]);
  if (strcmp(argv[1], password) == 0) {
    printf("password checks out\n");
    printf("MSG: %s\n", buffer);
  } else {
    printf("password error!\n");
  }
}
