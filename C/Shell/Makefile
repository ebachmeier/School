CC=gcc
CFLAGS=-Wall -g -c -std=c99
LFLAGS=-Wall -g

all: shell

shell: Shell.o StringQueue.o StringArray.o
	$(CC) $(LFLAGS) -o $@ $^

Shell.o: Shell.c
	$(CC) $(CFLAGS) -o $@ $<

StringQueue.o: StringQueue.c StringQueue.h
	$(CC) $(CFLAGS) -o $@ $<

StringArray.o: StringArray.c StringArray.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o shell
