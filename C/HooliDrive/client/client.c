/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 2
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * November 9, 2015
 * client.c accepts command line arguments for the server, port, directory, username, and password. It connects to the server and sends the list of files.
 *
 * Compile and Run:    $ make
 *                     $ ./client -v -s example.com -p 5555 -d /tmp username password
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "files.h"

#define MAX_SIZE 4096
#define LINE_SIZE 256

void receive_auth(int sockfd, char *dir);
void receive_files(int sockfd);

/*
 * get_sockaddr
 * This function gets the linked list of available sockets
 * Input:
 *      hostname - the hostname
 *      port - the port to try and connect on
 * Output: A linked list of socket addresses with their info
 */
struct addrinfo* get_sockaddr(const char* hostname, const char* port) {
    
    // variable declarations for the return values
    struct addrinfo hints;
    struct addrinfo* results;
    int retval;
    
    // copies 0 to the address info of hints
    memset(&hints, 0, sizeof(struct addrinfo));
    
    // return socket addresses for the server's IPv4 addresses
    hints.ai_family = AF_INET;
    
    // return TCP socket addresses
    hints.ai_socktype = SOCK_STREAM;
    
    // get the address info and return the integer response
    retval = getaddrinfo(NULL, port, &hints, &results);
    if (retval != 0) {
        syslog(LOG_ERR, "Error in getaddrinfo: %s\n", gai_strerror(retval));
        exit(EXIT_FAILURE);
    }
    return results;
}

/*
 * open_connection
 * This function opens a connection with an available socket
 * Input:
 *      addr_list - the list of available addresses
 * Output: A socket as an integer
 */
int open_connection(struct addrinfo* addr_list) {
    
    // variable declarations for the address and socket
    struct addrinfo* addr;
    int sockfd;
    
    // iterating through the list until we can connect to a socket
    for (addr = addr_list; addr != NULL; addr = addr->ai_next) {
        
        // open a socket
        sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        
        // go to the next socket and try to connect
        if (sockfd == -1)
            continue;
        // we can stop if we get a successful connection
        if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) != -1)
            break;
    }
    
    // free the allocated memory for the list of sockets
    freeaddrinfo(addr_list);
    
    // error message if we couldn't connect to any of the sockets
    if (addr == NULL) {
        syslog(LOG_ERR, "Unable to connect");
        exit(EXIT_FAILURE);
    }
    else {
        return sockfd;
    }
}

void upload_files_handler(char* msg) {
    
    char *token;
    char* savePointer;
    char *tokenFile;
    char filesNeeded[MAX_SIZE];
    
    char* temp = malloc(MAX_SIZE);
    memcpy(temp, msg, strlen(msg));
    temp[strlen(msg)] = '\0';
    
    token = strtok_r(temp, "\n", &savePointer);
    token = strtok_r(NULL, ":", &savePointer);
    int mLength = atoi(strtok_r(NULL, "\n", &savePointer));
    token = strtok_r(NULL, "\n", &savePointer);
    
    while (mLength > 0) {
        tokenFile = strtok_r(NULL, "\n", &savePointer);
        strcat(filesNeeded, tokenFile);
        strcat(filesNeeded, "\n");
    }
    tokenFile = strtok_r(NULL, "\0", &savePointer);
    strcat(filesNeeded, tokenFile);
    strcat(filesNeeded, "\n");
    syslog(LOG_INFO, "Files needed by server:\n%s", filesNeeded);
    strcat(temp, token);
    free(temp);
}

void files_list_handler(char* msg, int sockfd, char *dir) {
    
    char *token;
    char* savePointer;
    char *tokenReturn;
    char filesList[MAX_SIZE];
    
    char* temp = malloc(MAX_SIZE);
    memcpy(temp, msg, strlen(msg));
    temp[strlen(msg)] = '\0';

    token = strtok_r(temp, "\n", &savePointer);
    token = strtok_r(NULL, ":", &savePointer);
    tokenReturn = strtok_r(NULL, "\n", &savePointer);
    strcat(tokenReturn, "\0");
    
    // call the search method to traverse the file tree and output the files with checksums to file specified in the second argument
    FILE *tempFile = fopen("temp.txt", "a");
    syslog(LOG_INFO, "Scanning directory: %s", dir);
    searchDirectory(dir, "", tempFile);
    fclose(tempFile);
    
    // get the files and checksums from the temporary text file
    // generate LIST here
    tempFile = fopen("temp.txt", "r");
    char *tokenOne;
    if(tempFile != NULL) {
        char line[LINE_SIZE];
        while(fgets(line, sizeof line, tempFile) != NULL) {
            tokenOne = strtok(line, ",");
            strcat(filesList, tokenOne);
            strcat(filesList, "\n");
            tokenOne = strtok(NULL,"\n");
            strcat(filesList, tokenOne);
            strcat(filesList, "\n");
        }
    }
    else {
        syslog(LOG_ERR, "Unable to read the checksums from file");
    }
    fclose(tempFile);
    remove("temp.txt");
    
    // generate LIST message
    char listLength[LINE_SIZE];
    snprintf(listLength, sizeof(listLength), "%zu", strlen(filesList));
    char *command = "LIST\nToken:";
    char *header = "\nLength:";
    char *body = "\n\n";
    int length = strlen(command) + strlen(tokenReturn) + strlen(header) +
    strlen(listLength) + strlen(body) + strlen(filesList);
    char msgList[length];
    snprintf(msgList, length + 1, "%s%s%s%s%s%s", command, tokenReturn, header, listLength, body, filesList);
    
    // send the message to the server
    if (send(sockfd, msgList, strlen(msgList), 0) == -1) {
        syslog(LOG_ERR, "Unable to send message to server");
        free(temp);
        exit(EXIT_FAILURE);
    }
    syslog(LOG_INFO, "Message sent successfully to server");
    syslog(LOG_DEBUG, "Data sent:\n%s", msgList);
    strcat(temp, token);
    free(temp);
}

void receive_auth(int sockfd, char *dir) {
    
    // buffer to recieve the message
    char buffer[MAX_SIZE];
    // integer for the number of bytes read from the reply
    int bytes_read;
    
    // read the server reply
    bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read > 0) {
        
        // add terminating null to end of message
        buffer[bytes_read] = '\0';
        
        // print the receieved message
        syslog(LOG_DEBUG, "Message received (%d bytes):\n%s", bytes_read, buffer);
        
        // parse the recieved message
        char compare[4];
        strncpy(compare, buffer, 3);
        compare[3] = '\0';
        
        // if we recieve a 200 reply, populate a list of files
        if (strcmp(compare, "200") == 0) {
            
            files_list_handler(buffer, sockfd, dir);
            
        }
        else if (strcmp(compare, "401") == 0) {
            syslog(LOG_INFO, "Your login information was incorrect, please try again");
            exit(EXIT_FAILURE);
        }
        else {
            syslog(LOG_ERR, "The reply command was not recognized");
            exit(EXIT_FAILURE);
        }
    }
    else {
        syslog(LOG_ERR, "Error reading server response message");
        exit(EXIT_FAILURE);
    }
}

void receive_files(int sockfd) {
    
    // buffer to recieve the message
    char buffer[MAX_SIZE];
    // integer for the number of bytes read from the reply
    int bytes_read;
    
    // read the server reply
    bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read > 0) {
        
        // add terminating null to end of message
        buffer[bytes_read] = '\0';
        
        // print the receieved message
        syslog(LOG_DEBUG, "Message received (%d bytes):\n%s", bytes_read, buffer);
        
        // parse the recieved message
        char compare[4];
        strncpy(compare, buffer, 3);
        compare[3] = '\0';
        
        if (strcmp(compare, "302") == 0) {
            
            upload_files_handler(buffer);
            
        }
        else if (strcmp(compare, "204") == 0) {
            syslog(LOG_INFO, "All files are up-to-date on the server");
            exit(EXIT_SUCCESS);
        }
        else {
            syslog(LOG_ERR, "The reply command was not recognized");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else {
        syslog(LOG_ERR, "Error reading server response message");
        exit(EXIT_FAILURE);
    }
}


/*
 * main method
 * The main method makes calls to other methods to search the passed file directory and send the list of files to the server
 * Input parameters: flags --verbose, --server, --port, --dir, username, and a password
 * Output: None
 */
int main(int argc, char** argv) {
    
    int c, option_index = 0;
    bool s, x, d;
    char *username, *password, *server, *port, *dir, *pTry, *uTry;
    
    // open system log and default to recording up to INFO
    openlog("client", LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    setlogmask(LOG_UPTO(LOG_INFO));
    syslog(LOG_INFO, "Client Initialized");
    
    static struct option long_options[] =
    {
        {"verbose", no_argument, 0, 'v'},
        {"server", optional_argument, 0, 's'},
        {"port", optional_argument, 0, 'x'},
        {"dir", optional_argument, 0, 'd'},
        {0, 0, 0, 0}
    };
    
    while ((c = getopt_long(argc, argv, "vs:x:d:", long_options, &option_index)) != -1) {
        
        switch (c) {
                
            case 'v':
                setlogmask(LOG_UPTO(LOG_DEBUG));
                break;
            case 's':
                s = 1;
                server = strdup(optarg);
                break;
            case 'x':
                x = 1;
                port = strdup(optarg);
                break;
            case 'd':
                d = 1;
                dir = strdup(optarg);
                break;
            case '?':
                return EXIT_FAILURE;
                break;
        }
        
        // get the username and password
        int i = optind;
        uTry = argv[i++];
        pTry = argv[i++];
    }
    if (uTry != NULL) {
        username = uTry;
    }
    else {
        syslog(LOG_ERR, "No username specified");
        exit(EXIT_FAILURE);
    }
    if (pTry != NULL) {
        password = pTry;
    }
    else {
        syslog(LOG_ERR, "No password specified");
        exit(EXIT_FAILURE);
    }
    if(!s) {
        // if no server is specified, connect to localhost
        syslog(LOG_WARNING, "No server specified, using localhost");
        server = "127.0.0.1";
    }
    if(!x) {
        // if no port is specified, use 9000
        syslog(LOG_WARNING, "No port specified, using port 9000");
        port = "9000";
    }
    if(!d) {
        // if no directory is specified, use ~/hooli
        syslog(LOG_WARNING, "No directory specified, using ~/hooli");
        dir = "~/hooli";
    }
    
    syslog(LOG_DEBUG, "Username is %s", username);
    syslog(LOG_DEBUG, "Password is %s", password);
    syslog(LOG_DEBUG, "Server is %s", server);
    syslog(LOG_DEBUG, "Port is %s", port);
    syslog(LOG_DEBUG, "Directory to search is %s", dir);
    
    // create a temporary file pointer for the files and checksums
    fclose(fopen("temp.txt", "w"));
    
    // connect to the server
    struct addrinfo* results = get_sockaddr(server, port);
    int sockfd = open_connection(results);
    
    // send an AUTH request
    char *command = "AUTH\nUsername:";
    char *header = "\nPassword:";
    char *body = "\n\n";
    int length = strlen(command) + strlen(username) + strlen(header) +
    strlen(password) + strlen(body);
    char msgAuth[length];
    snprintf(msgAuth, length, "%s%s%s%s%s", command, username, header, password, body);
    
    // send the message to the server
    if (send(sockfd, msgAuth, strlen(msgAuth), 0) == -1) {
        syslog(LOG_ERR, "Unable to send message to server");
        exit(EXIT_FAILURE);
    }
    syslog(LOG_INFO, "Message sent successfully to server");
    syslog(LOG_DEBUG, "Data sent:\n%s", msgAuth);
    
    receive_auth(sockfd, dir);
    
    receive_files(sockfd);

    // Close the socket and exit
    close(sockfd);
    
    // Close the sys log
    closelog();
    
    exit(EXIT_SUCCESS);
}
