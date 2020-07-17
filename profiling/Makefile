CC = clang
CFLAGS = -g -finstrument-functions
# In order to have consistent memory layout, we use this flag
# https://en.wikipedia.org/wiki/Position-independent_code
LFLAGS = -no-pie

all: prof_example

prof_example: profiler.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o prof_example
