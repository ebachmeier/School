/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 2
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * November 11, 2015
 * hmds.c accepts command line arguments for the port and hostname. It connects to the client and gives a reply.
 *
 * Compile and Run:    $ make
 *                     $ ./hmds -v -p 5555 -r example.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <getopt.h>
#include <stdbool.h>
#include <signal.h>
#include "../hdb/hdb.h"
#include<errno.h>

#define BACKLOG 25
#define LINE_SIZE 256
#define MAX_SIZE 4096

static bool term_requested = false;
void auth_request_handler(char* msg, hdb_connection *con, int sockfd);
void list_request_handler(char* msg, hdb_connection *con, int sockfd);

/*
 * handle_connection
 * This function reads bytes fromt the client connection
 * Input:
 *      connectionfd - the incoming connection
 * Output: None
 */
void handle_connection(int connectionfd, char *hostname)
{
    char buffer[MAX_SIZE];
    int bytes_read;
    // loop while their is data being read in
    do {
        
        // Read up to 4095 bytes from the client
        bytes_read = recv(connectionfd, buffer, sizeof(buffer)-1, 0);
    
        // Add a terminating NULL character and print the message received
        buffer[bytes_read] = '\0';
        syslog(LOG_DEBUG, "Message received (%d bytes):\n%s\n", bytes_read, buffer);
        
        // parse the recieved message
        char compare[5];
        strncpy(compare, buffer, 4);
        compare[4] = '\0';
    
        // connect to Redis
        hdb_connection* con = hdb_connect(hostname);
        
        // if we recieve an AUTH command, verify the login and print the username
        if (strcmp(compare, "AUTH") == 0) {
            
            auth_request_handler(buffer, con, connectionfd);
            
        }
        else if (strcmp(compare, "LIST") == 0) {
            
            list_request_handler(buffer, con, connectionfd);
            
        }
        // Disconnect from the Redis server
        hdb_disconnect(con);
    } while (bytes_read > 0 && !term_requested);
    
    if (bytes_read == -1 || bytes_read < 1) {
        // Otherwise, if the read failed
        syslog(LOG_ERR, "Unable to read from socket");
        exit(EXIT_FAILURE);
    }
}

void term_handler(int signal)
{
    syslog(LOG_DEBUG, "Termination requested");
    term_requested = true;
}

void auth_request_handler(char* msg, hdb_connection *con, int sockfd) {
    
    char* token;
    char* savePointer;
    char *username, *password;
    
    char* temp = malloc(MAX_SIZE);
    memcpy(temp, msg, strlen(msg));
    temp[strlen(msg)] = '\0';
    
    token = strtok_r(temp, "\n", &savePointer);
    
    token = strtok_r(NULL, ":", &savePointer);
    username = strtok_r(NULL, "\n", &savePointer);
    strcat(username, "\0");
    
    token = strtok_r(savePointer, ":", &savePointer);
    password = strtok_r(NULL, "\n", &savePointer);
    strcat(password, "\0");
    
    // authenticate the user with the Redis database
    char * userToken = NULL;
    syslog(LOG_INFO, "Authenticating user %s", username);
    userToken = hdb_authenticate(con, username, password);
    token = strcat(token, "null");
    
    char* msgSend;
    char *header, *body;
    int length;
    
    // if there is a token returned, send a 200 response
    if (userToken != NULL) {
        header = "200 Authentication successful\nToken:";
        body = "\n\n";
        length = strlen(header) + strlen(userToken) + strlen(body);
        msgSend = malloc(length * sizeof(char));
        snprintf(msgSend, length + 1, "%s%s%s", header, userToken, body);
        //free(userToken);
    }
    else {
        header = "401 Unauthorized\n\n";
        length = strlen(header);
        msgSend = malloc(length * sizeof(char));
        snprintf(msgSend, length + 1, "%s", header);
        //free(userToken);
    }

    // send the message to the server
    if (send(sockfd, msgSend, strlen(msgSend), 0) == -1) {
        syslog(LOG_ERR, "Unable to send message to server");
        free(msgSend);
        exit(EXIT_FAILURE);
    }

    syslog(LOG_INFO, "Message sent successfully to server");
    syslog(LOG_DEBUG, "Data sent:\n%s", msgSend);
    free(msgSend);
}

void list_request_handler(char* msg, hdb_connection *con, int sockfd) {
    
    char* token;
    char* savePointer;
    char *tokenReturn, *tokenVerify;
    
    char filesRec[MAX_SIZE];
    char filesNeeded[MAX_SIZE];
    
    // tokenize the username from the buffer
    char* temp = malloc(MAX_SIZE);
    memcpy(temp, msg, strlen(msg));
    temp[strlen(msg)] = '\0';
    
    token = strtok_r(temp, "\n", &savePointer);
    
    token = strtok_r(NULL, ":", &savePointer);
    tokenVerify = strtok_r(NULL, "\n", &savePointer);
    strcat(tokenReturn, "\0");
    
    tokenReturn = hdb_verify_token(con, tokenVerify);
    
    int mLength = atoi(strtok_r(NULL, "\n", &savePointer));
    token = strtok_r(NULL, "\n", &savePointer);
   token = strcat(token, "null");
    
    // if the user does exist with that token in the database, print the requested files and check which we already have
    if (tokenReturn != NULL && mLength > 0) {
        char *tokenFile, *checksum;
        while (mLength > 0) {
            tokenFile = strtok_r(NULL, "\n", &savePointer);
            strcat(tokenFile, "\0");
            checksum = strtok_r(NULL, "\n", &savePointer);
            strcat(checksum, "\0");
            strcat(filesRec, tokenFile);
            strcat(filesRec, "\n");
            // if the file isn't on Redis, add it to server list
            if (hdb_file_exists(con, tokenReturn, tokenFile)) {
                // if the file has a different checksum than previous copy, add it to server list
                if (hdb_file_checksum(con, tokenReturn, tokenFile) != checksum) {
                    strcat(filesNeeded, tokenFile);
                    strcat(filesNeeded, "\n");
                }
            }
            // we also need the file if it doesn't exist on the Redis server
            else {
                strcat(filesNeeded, tokenFile);
                strcat(filesNeeded, "\n");
            }
            mLength -= (strlen(tokenFile) + strlen(checksum) + 2);
        }
        
        syslog(LOG_DEBUG, "Files sent by client:\n%s", filesRec);
        
        syslog(LOG_DEBUG, "Checking over files in server");
        
        char listLength[LINE_SIZE];
        snprintf(listLength, sizeof(listLength), "%zu", strlen(filesNeeded));
        
        char *headerList = "302 Files requested\nLength:";
        char *bodyList = "\n\n";
        int lengthMsg = strlen(headerList) + strlen(listLength) + strlen(bodyList);
        char msgFiles[lengthMsg];
        snprintf(msgFiles, lengthMsg, "%s%s%s", headerList, listLength, bodyList);
        
        // send the message to the server
        if (send(sockfd, msgFiles, strlen(msgFiles), 0) == -1) {
            syslog(LOG_ERR, "Unable to send message to server");
            exit(EXIT_FAILURE);
        }
        syslog(LOG_INFO, "Message sent successfully to server");
        syslog(LOG_DEBUG, "Data sent:\n%s", msgFiles);
        term_requested = true;
        
    } // otherwise, send a 204 message
    else {
        char *headerNoList = "204 No files requested\n\n";
        int lengthNoList = strlen(headerNoList);
        char msgNoList[lengthNoList];
        snprintf(msgNoList, lengthNoList, "%s", headerNoList);
        
        // send the message to the server
        if (send(sockfd, msgNoList, strlen(msgNoList), 0) == -1) {
            syslog(LOG_ERR, "Unable to send message to server");
            exit(EXIT_FAILURE);
        }
        syslog(LOG_INFO, "Message sent successfully to server");
        syslog(LOG_DEBUG, "Data sent:\n%s", msgNoList);
        term_requested = true;
    }
}

/*
 * get_server_sockaddr
 * This function gets the linked list of available sockets to connect to
 * Input:
 *      port - the port to try and connect on
 * Output: A linked list of socket addresses with their info
 */
struct addrinfo* get_server_sockaddr(const char* port) {
    
    // variable declarationsf for the return values
    struct addrinfo hints;
    struct addrinfo* results;
    int retval;
    
    // copies 0 to the address info of hints
    memset(&hints, 0, sizeof(struct addrinfo));
    
    // return socket addresses for our local IPv4 addresses
    hints.ai_family = AF_INET;
    
    // return TCP socket addresses
    hints.ai_socktype = SOCK_STREAM;
    
    // socket addresses should be listening sockets
    hints.ai_flags = AI_PASSIVE;
    
    // get the address info and return the integer response
    retval = getaddrinfo(NULL, port, &hints, &results);
    if (retval != 0) {
        syslog(LOG_ERR, "%s", gai_strerror(retval));
        exit(EXIT_FAILURE);    }
    return results;
}

/*
 * bind_socket
 * This function connects the socket to a local address
 * Input:
 *      addr_list - the list of available addresses
 * Output: A socket as an integer
 */
int bind_socket(struct addrinfo* addr_list) {
    struct addrinfo* addr;
    int sockfd;
    char yes = '1';
    // Iterate through each addrinfo in the list; stop when we successfully bind
    // to one
    for (addr = addr_list; addr != NULL; addr = addr->ai_next) {
        // Open a socket
        sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        // Try the next address if we couldn't open a socket
        if (sockfd == -1)
            continue;
        // Allow the port to be re-used if currently in the TIME_WAIT state
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("Unable to set socket option");
            exit(EXIT_FAILURE);
        }
        // Try to bind the socket to the address/port
        if (bind(sockfd, addr->ai_addr, addr->ai_addrlen) == -1) {
            // If binding fails, close the socket, and try the next address
            close(sockfd);
            continue;
        } else {
            // Otherwise, we've bound the address/port to the socket, so stop
            // processing
            break;
        }
    }
    // Free the memory allocated to the addrinfo list
    freeaddrinfo(addr_list);
    // If addr is NULL, we tried every addrinfo and weren't able to bind to any
    if (addr == NULL) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    } else {
        // Otherwise, return the socket descriptor
        return sockfd;
    }
}

/*
 * wait_for_connection
 * This function waits for a connection on the given socket
 * Input:
 *      sockfd - the integer number of the given sokcket
 * Output: A integer value of the connection status
 */
int wait_for_connection(int sockfd) {
    struct sockaddr_in client_addr; // Remote IP that is connecting to us
    socklen_t addr_len = sizeof(struct sockaddr_in); // Length of the remote IP structure
    char ip_address[INET_ADDRSTRLEN]; // Buffer to store human-friendly IP address
    int connectionfd; // Socket file descriptor for the new connection
    // Wait for a new connection
    connectionfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
    // Make sure the connection was established successfully
    if (connectionfd == -1) {
        syslog(LOG_ERR, "Unable to accept connection");
        exit(EXIT_FAILURE);
    }
    // Convert the connecting IP to a human-friendly form and print it
    inet_ntop(client_addr.sin_family, &client_addr.sin_addr, ip_address, sizeof(ip_address));
    syslog(LOG_INFO, "Connection accepted from %s", ip_address);
    // Return the socket file descriptor for the new connection
    return connectionfd;
}

int main(int argc, char** argv) {
    
    int c, option_index = 0;
    bool p, r;
    char *port, *hostname;
    
    // open system log and default to recording all logs (debug)
    openlog("server", LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    setlogmask(LOG_UPTO(LOG_INFO));
    syslog(LOG_INFO, "Server Initialized");
    
    static struct option long_options[] =
    {
        {"verbose", no_argument, 0, 'v'},
        {"port", optional_argument, 0, 'p'},
        {"redis", optional_argument, 0, 'r'},
        {0, 0, 0, 0}
    };
    
    while ((c = getopt_long(argc, argv, "vp:r:", long_options, &option_index)) != -1) {
        
        switch (c) {
                
            case 'v':
                setlogmask(LOG_UPTO(LOG_DEBUG));
                break;
            case 'p':
                p = 1;
                port = strdup(optarg);
                break;
            case 'r':
                r = 1;
                hostname = strdup(optarg);
                break;
            case '?':
                return EXIT_FAILURE;
                break;
        }
    }
    
    if(!p) {
        syslog(LOG_ERR, "No port specified, using 9000");
        port = "9000";
    }
    if(!r) {
        syslog(LOG_ERR, "No Redis server specified, using localhost");
        hostname = "127.0.0.1";
    }
    
    syslog(LOG_INFO, "Server is %s", hostname);
    syslog(LOG_INFO, "Port is %s", port);
    
    term_requested = false;
    
    // We want to listen on port 5000
    struct addrinfo* results = get_server_sockaddr(port);
    
    // Create a listening socket
    int sockfd = bind_socket(results);
    
    // Start listening on the socket
    if (listen(sockfd, BACKLOG) == -1) {
        perror("Unable to listen on socket");
        exit(EXIT_FAILURE);
    }
    
    int connectionfd;
    while (!term_requested) {
        // Wait for a connection and handle it
        connectionfd = wait_for_connection(sockfd);
        handle_connection(connectionfd, hostname);
    }
    // Close the connection
    close(connectionfd);    
    exit(EXIT_SUCCESS);
}
