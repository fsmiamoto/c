#ifndef POPEN3_H
#define POPEN3_H

#include <stdio.h>

typedef struct {
  FILE *in, *out, *err;
} stdpipes;

stdpipes popen3(const char *command);

#endif
