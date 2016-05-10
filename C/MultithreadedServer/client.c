/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 3
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * March 16, 2016
 *
 * To compile and run:
 * 		$ make
 *		$ ./client 127.0.0.1 5555 7
 *                 hostname  port number_to_send
 *
 * client.c connects to the multi-threaded server and sends a number that is to be sent 
 * back multiplied by 10.
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define MAX_MSG_SIZE 1024

/*
 * get_sockaddr method
 * Author: Eric Bachmeier
 * Created: March 17, 2016
 * Purpose: This function converts the server's address and port into a form usable to 
 * create a socket.
 * Input Parameters:
 *		hostname - the server address of the host machine
 *		port - the port on which to connect on
 * Output: A struct addrinfo for a socket
 */
struct addrinfo * get_sockaddr(const char * hostname,
    const char * port) {

    struct addrinfo hints;
    struct addrinfo * results;
    int rv;

    memset( & hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, port, & hints, & results) != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(rv));
        exit(1);
    }

    return results;
}

/*
 * open_connection method
 * Author: Eric Bachmeier
 * Created: March 18, 2016
 * Purpose: This function establishes a connection with the desired server.
 * Input Parameters: 
 *		addr_list - the address with the hostname and port
 * Output: The opened connection
 */
int open_connection(struct addrinfo * addr_list) {

    struct addrinfo * p;
    int sockfd;

    for (p = addr_list; p != NULL; p = p->ai_next) {

        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        // try the next address since the socket operation failed
        if (sockfd == -1) continue;

        // stop iterating of we are able to connect to the server

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) != -1) break;
    }

    freeaddrinfo(addr_list);

    if (p == NULL)
        err(EXIT_FAILURE, "%s", "Unable to connect");
    else
        return sockfd;

}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 18, 2016
 * Purpose: This function is the main method for executing the client. It takes input from
 * the command-line for the hostname, port number to listen on, and the number to send the server.
 * Input Parameters: None
 * Output: Integer status for the exit code
 */
int main(int argc, char * argv[]) {

    int numbytes;
    char sendBuff[MAX_MSG_SIZE];
    char recvBuff[MAX_MSG_SIZE];
    struct sockaddr_in serv_addr;
    struct hostent * server;
    int rv;
    int product;

    if (argc != 4) {
        printf("\n\tUsage: %s hostname port number_to_send\n\n", argv[0]);
        return 1;
    }

    struct addrinfo * results = get_sockaddr(argv[1], argv[2]);
    int sockfd = open_connection(results);

    memset(sendBuff, '0', sizeof(sendBuff));
    memset(recvBuff, '0', sizeof(recvBuff));

    snprintf(sendBuff, sizeof(sendBuff), "%s", argv[3]);
    write(sockfd, sendBuff, strlen(sendBuff));

    numbytes = recv(sockfd, recvBuff, sizeof(recvBuff) - 1, 0);
    if (numbytes == -1) {
        perror("recv");
        exit(1);
    }

    recvBuff[numbytes] = '\0';
    sscanf(recvBuff, "%d", & product);
    printf("\tReceived product of %d\n", product);

    return 0;
}