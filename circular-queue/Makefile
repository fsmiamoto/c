CC = clang
CFLAGS = -g -Wall -Werror
OBJS = queue

all: queue

%: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o main
