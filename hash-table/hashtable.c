// A simple hash table in C
// Completely based on the source code shown at
// https://www.youtube.com/watch?v=2Ti5yvumFTU
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
  char name[MAX_NAME];
  int age;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
  unsigned int hash;
  for (int i = 0; i < strnlen(name, MAX_NAME); i++) {
    hash += name[i];
    hash *= name[i];
  }
  return hash % TABLE_SIZE;
}

bool equal(const char *a, const char *b) {
  return strncmp(a, b, MAX_NAME) == 0;
}

void init_hash_table() {
  for (int i = 0; i < TABLE_SIZE; i++)
    hash_table[i] = NULL;
}

bool hash_table_insert(person *p) {
  if (p == NULL)
    return false;
  int index = hash(p->name);
  if (hash_table[index] != NULL) {
    return false;
  }
  hash_table[index] = p;
  return true;
}

void print_table() {
  printf("Start\n");
  for (int i = 0; i < TABLE_SIZE; i++)
    if (hash_table[i] == NULL) {
      printf("\t%i\t---\n", i);
    } else {
      printf("\t%i\t%s\n", i, hash_table[i]->name);
    }
  printf("End\n");
}

person *hash_table_lookup(char *name) {
  int index = hash(name);
  if (hash_table[index] != NULL && equal(hash_table[index]->name, name)) {
    return hash_table[index];
  }

  return NULL;
}

person *hash_table_delete(char *name) {
  int index = hash(name);
  person *p = hash_table[index];
  hash_table[index] = NULL;
  return p;
}

int main() {
  init_hash_table();
  print_table();

  person eren = {.name = "Eren", .age = 21};
  person mikasa = {.name = "Mikasa", .age = 22};
  person armin = {.name = "Armin", .age = 23};

  hash_table_insert(&eren);
  hash_table_insert(&armin);
  hash_table_insert(&mikasa);

  hash_table_delete("Mikasa");

  print_table();
}
