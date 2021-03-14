CC=clang
CFLAGS=-Wall -g

OBJS=popen3.o
BINS=testprogram plain_popen popen3_example

all: $(BINS)

popen3_example: popen3_example.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(BINS) $(OBJS) *.dSYM
