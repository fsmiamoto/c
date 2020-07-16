#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In C, memory has no type information,
// all types are defined by how we read/write to memory

typedef struct person {
  int age;
  int height;
  char name[10];
} person_t;

int main() {
  void *p = malloc(100);

  bzero(p, 100);

  person_t *person = (person_t *)p;

  person->age = 99;
  person->height = 245;
  strncpy(person->name, "Bill", sizeof(person->name) - 1);

  int *iptr = (int *)(person + 1);

  *iptr = 0xFEEDBEFF;

  printf("Done!\n");
}
