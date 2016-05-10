CC=gcc

all: client server

client: client.c
	$(CC) -o $@ $^

server: server.c
	$(CC) -o $@ $^ -lpthread

clean:
	rm -f *.o client server
