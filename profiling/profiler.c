#include <stdio.h>

// These functions are called whenever there is a function call
// You need a special flag when compiling, see the Makefile
void __cyg_profile_func_enter(void *this_func, void *call_site)
    __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_func, void *call_site)
    __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_func, void *call_site) {
  printf("--> %p %p\n", this_func, call_site);
}
void __cyg_profile_func_exit(void *this_func, void *call_site) {
  printf("<-- %p %p\n", this_func, call_site);
}

// Since this instrumentation occurs at compile time, functions that
// were not compiled with it will not be instrumented.
// printf, for example, will not have any of the enter or exit calls

void func1() { printf("func1\n"); }

void func2() {
  printf("func2\n");
  func1();
}

int main() {
  func1();
  func2();
}
