#include <stdio.h>
#include <stdlib.h>

// You can get the enviroment with the arguments of main
// or you can use an external defined environ variable
extern char **environ;

int main(int argc, char **argv, char **envp) {

  // ! These changes do not affect envp but are visible on environ !
  // Add new variable
  putenv("PASS=1234");
  // Overwrite the path for this program
  setenv("PATH", "/bin/", 1);

  // Both options are NULL terminated
  for (int i = 0; environ[i] != NULL; i++) {
    printf("%d: %s\n", i, environ[i]);
  }
}
