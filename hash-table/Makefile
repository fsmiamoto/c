CC=gcc
CFLAGS=-Wall -g
BIN=hashtable

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(BIN)

