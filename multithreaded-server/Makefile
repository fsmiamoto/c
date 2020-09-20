CC = clang
CFLAGS = -g -Wall -lpthread
BINS = server client

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

client: client.go
	go build $^

many-clients: all
	bash manyclients.sh

clean:
	rm -rf *.dSYM $(BINS)
