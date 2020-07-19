CC = gcc
CFLAGS = -Wall -static
TAG = gcc-server

all: server

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

docker:
	docker build . -t $(TAG)

clean:
	rm -rf *.o server
