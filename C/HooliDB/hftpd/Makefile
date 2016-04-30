CC=gcc
CFLAGS=-Wall -Werror -g -c
LFLAGS=-Wall -Werror -g

all: hftpd

hftpd: hftpd.c ../common/udp_sockets.o ../common/udp_server.o ../common/udp_client.o ../common/hftp_messages.o
	$(CC) $(LFLAGS) -o $@ $^

udp_sockets.o: ../common/udp_sockets.c ../common/udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

udp_server.o: ../common/udp_server.c ../common/udp_server.h ../common/udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

udp_client.o: ../common/udp_client.c ../common/udp_client.h ../common/udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

hftp_messages.o: ../common/hftp_messages.c ../common/hftp_messages.h ../common/udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.a hftpd
