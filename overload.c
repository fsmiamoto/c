/* Based on listing 9.59 of the Low-Level programming book by Igor Zhirkov */
#include <stdio.h>


/* Uses C11 macro */
#define print_type(x) (_Generic( (x), \
    int: printf("I'm an int!\n"),\
    double: printf("I'm an double!\n"),\
    float: printf("I'm an float!\n")))

int main(void) {
    int x = 101;
    double y = 20.02;

    print_type(x);
    print_type(y);
    return 0;
}
