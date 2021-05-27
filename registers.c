// Source: https://www.netmeister.org/blog/stdarg.html
#include <stdint.h>
#include <stdio.h>

int add(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7,
        int arg8, int arg9) {
  int local;

  /* Look, Ma, we can inspect registers from
   * inside our program! */
  register uint64_t myrbp asm("rbp");
  register uint64_t myrsp asm("rsp");
  printf("Func1:\n");
  printf("-----\n");
  printf("rbp at                               : 0x%12lX\n",
         (unsigned long)myrbp);
  printf("rsp at                               : 0x%12lX\n",
         (unsigned long)myrsp);
  printf("\n");

  printf("first local var in func1 at          : 0x%12lX\n",
         (unsigned long)&local);
  printf("1st arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg1);
  printf("2nd arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg2);
  printf("3rd arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg3);
  printf("4th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg4);
  printf("5th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg5);
  printf("6th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg6);
  printf("7th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg7);
  printf("8th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg8);
  printf("9th arg to func at                   : 0x%12lX\n",
         (unsigned long)&arg9);
  local = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9;
  return local;
}

int main(int argc, char **argv) {
  int local;

  register uint64_t rbp asm("rbp");
  register uint64_t rsp asm("rsp");
  printf("Main:\n");
  printf("-----\n");
  printf("rbp (in main) at                     : 0x%12lX\n",
         (unsigned long)rbp);
  printf("rsp (in main) at                     : 0x%12lX\n",
         (unsigned long)rsp);
  printf("\n");
  printf("first local var in main at           : 0x%12lX\n",
         (unsigned long)&local);
  printf("\n");
  (void)add(1, 2, 3, 4, 5, 6, 7, 8, 9);
  return 0;
}
