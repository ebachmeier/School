CC=gcc
CFLAGS=-Wall -g -c -std=c99
LFLAGS=-Wall -g

all: ebachme_a1

ebachme_a1: Shell.o StringQueue.o StringArray.o
	$(CC) $(LFLAGS) -o $@ $^

Shell.o: Shell.c
	$(CC) $(CFLAGS) -o $@ $<

StringQueue.o: StringQueue.c StringQueue.h
	$(CC) $(CFLAGS) -o $@ $<

StringArray.o: StringArray.c StringArray.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o ebachme_a1
