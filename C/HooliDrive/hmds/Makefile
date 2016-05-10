hmds: hmds.c ../hdb/hdb.c
	gcc -Wall -Werror -g -O0 -lz -std=gnu11 -D_GNU_SOURCE -o hmds hmds.c ../hdb/hdb.c -lhiredis
clean:
	rm -f *.o *.a hmds
