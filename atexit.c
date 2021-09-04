#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clenaup() {
    printf("Cleaning up...\n");
}

int main(int argc, char** argv) {
    atexit(clenaup);

    if(argc == 3) {
        // the clenaup function is not called when exceptions occur
        // for that you'd need some signal handling.
        fputs("SOMETHING WENT WRONG :(\n", stderr);
        abort();
    }

    printf("Welcome\n");
    sleep(5);
    printf("Good bye\n");
}
