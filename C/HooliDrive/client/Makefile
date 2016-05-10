client: client.c files.c checksums.c
	gcc -Wall -Werror -g -O0 -std=gnu11 -o client client.c files.c checksums.c -lz -lhiredis
clean:
	rm -f *.o *.a client
