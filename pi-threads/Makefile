CC = gcc
CFLAGS = -g3 
LFLAGS = -lm -lpthread

# Default values
NUM_OF_THREADS = 8
NUM_OF_TERMS = 1000000000

BENCH_NUM_OF_RUNS = 10

all: build

build: pi.c
	$(CC) -D NUM_OF_THREADS=$(NUM_OF_THREADS) NUM_OF_TERMS=$(NUM_OF_TERMS) $(CFLAGS) -o pi $^ $(LFLAGS)

pi%threads: pi.c
	$(CC) -D NUM_OF_THREADS=$(@:pi%threads=%) -D NUM_OF_TERMS=$(NUM_OF_TERMS) $(CFLAGS) -o $@ $^ $(LFLAGS)

bench: pi2threads pi4threads pi8threads pi16threads pi32threads pi64threads
	@for bench in $^; do \
		echo -e "\nRunning $$bench $(BENCH_NUM_OF_RUNS) times for $(NUM_OF_TERMS) terms..."; \
		time ./run.sh "./$$bench" $(BENCH_NUM_OF_RUNS); \
	done

clean:
	rm -f pi pi*threads
