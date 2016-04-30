CC=gcc
CFLAGS=-Wall -g -std=c99

all: simulator

simulator: simulator.c deq.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o simulator
