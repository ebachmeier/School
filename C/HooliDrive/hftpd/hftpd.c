/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 3
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * November 30, 2015
 * hftpd.c accepts command line arguments for the port, redis hostname, directory for 
 * uploaded files, the time to wait before exiting, and and a verbose flag. The server
 * receives files from the client for reliable file transfers.
 *
 * Compile and Run:    $ make
 *                     $ ./hftpd -v -r example.com -p 5555 -d /tmp -t 15
 */

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <syslog.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../common/udp_sockets.h"
#include "../common/udp_server.h"
#include "../common/udp_client.h"
#include "../common/hftp_messages.h"

/*
 * getOptions
 * This function gets and parses the command line options from the user
 * Input:
 *      argc - the number of arguments
 *      argv - the arguments array
 *      timewait - the time to wait until exit integer
 *      port - the port number for which to listen on
 * Output: None
 */
void getOptions(int argc, char** argv, int* timewait, char** port, char** dir, char** hostname) {

    int c;
    
    // Parse the command line options for port, redis host, and directory for file upload
    while (true) {
    
        static struct option long_options[] =
    	{
        	{"verbose", no_argument, 0, 'v'},
        	{"redis", optional_argument, 0, 'r'},
        	{"port", optional_argument, 0, 'p'},
        	{"dir", optional_argument, 0, 'd'},
        	{"timewait", optional_argument, 0, 't'},
        	{0, 0, 0, 0}
    	};

        int option_index = 0;
        
        c = getopt_long(argc, argv, "vr:p:d:t:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 'p':
                *port = optarg;
                syslog(LOG_INFO, "Listening on port %s", *port);
                break;
            case 't':
                *timewait = atoi(optarg);
                syslog(LOG_INFO, "Timeout set to %d seconds", *timewait);
                break;
            case 'd':
                *dir = optarg;
                syslog(LOG_INFO, "Upload directory set to %s", *dir);
                break;
            case 'r':
                *hostname = optarg;
                syslog(LOG_INFO, "Redis host %s", *hostname);
                break;
            case 'v':
                setlogmask(LOG_UPTO(LOG_DEBUG));
                syslog(LOG_INFO, "Verbose mode on");
                break;
            case '?':
                break;
        }
    }
}

/*
 * create_data_ack_message
 * This function creates the response to a data message
 * Input: None
 * Output: A hftp_message of 4 bytes
 */
hftp_message* create_data_ack_message(int sequenceNumberIncoming) {

    hftp_data_message* msg = (hftp_data_message*) create_hftp_message();
    msg->ack = ACK_TYPE1_ACK;
    msg->sequenceNumber = sequenceNumberIncoming;
    
    // Length of 32 bits
    msg->length = 4;
    
    return (hftp_message*)msg;
}

/*
 * create_type1_control_ack_response
 * This function creates the response to a type 1 control message that initiates a connection
 * Input: None
 * Output: A hftp_message of 4 bytes, containing the type, sequence, and error code
 */
hftp_message* create_type1_control_ack_response() {

    hftp_control_message* msg = (hftp_control_message*) create_hftp_message();
    msg->ack = ACK_TYPE1_ACK;
    msg->sequenceNumber = 0;

    // 32 bits to store the type, sequence number, and any error code
    msg->length = 4;

    return (hftp_message*) msg;
}

/*
 * create_type2_control_ack_response
 * This function creates the response to a type 2 control message that terminates
 * Input:
 *      sequenceNumberIncoming - The sequence number we are replying to
 * Output: A hftp_message of 4 bytes, containing the type, sequence, and error code
 */
hftp_message* create_type2_control_ack_response(int sequenceNumberIncoming) {

    hftp_control_message* msg = (hftp_control_message*) create_hftp_message();
    msg->ack = ACK_TYPE1_ACK;
    msg->sequenceNumber = sequenceNumberIncoming;

    // 32 bits to store the type, sequence number, and any error code
    msg->length = 4;

    return (hftp_message*) msg;
}

/*
 * main method
 * The main method makes calls to other methods to send and receive hftp messages
 * Input parameters: flags --verbose, --redis, --port, --dir, --timewait
 * Output: None
 */
int main(int argc, char** argv) {

	// Open system log and default to recording up to INFO
    openlog("hftpd", LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    setlogmask(LOG_UPTO(LOG_INFO));
    syslog(LOG_INFO, "Server Initialized");

    static int timewait  = 0;
    char* port = NULL;
    char* dir = NULL;
    char* hostname = NULL;

    char fileName[1460]; //////// 1440
    int fileSize = 0;

    getOptions(argc, argv, &timewait, &port, &dir, &hostname);

    if (port == NULL) {
        syslog(LOG_INFO, "A port needs to be specified with -p / --port");
        exit(EXIT_FAILURE);
    }
    
    if (hostname == NULL) {
    	hostname = "127.0.0.1";
        syslog(LOG_INFO, "No host specified, using localhost");
    }
    
    if (dir == NULL) {
        dir = "/tmp/hftpd";
        // CHECK IF IT EXISTS
        syslog(LOG_INFO, "No upload directory specified, using /tmp/hftpd");
    }
    
    if (timewait == 0) {
        timewait = 10;
        syslog(LOG_INFO, "Using default timewait of 10 seconds before exit");
    }
    
    syslog(LOG_DEBUG, "Valid arguments given");

    int sockfd = create_server_socket(port);

    hftp_control_message* control_message_init;
    hftp_data_message* data_message;
    hftp_message* data_message_ack;
    hftp_message* control_response_type1;
    
    host client;

    syslog(LOG_DEBUG, "Socket created");
    
    control_response_type1 = create_type1_control_ack_response();

    syslog(LOG_DEBUG, "Created response to control (Type 1)");

	// Wait for a reply
    while (true) {
    
        syslog(LOG_DEBUG, "Waiting for control message (Type 1)");

        control_message_init = (hftp_control_message*) receive_hftp_message(sockfd, &client);
		
		// If the type is type 1 for initiation, send our reply
        if (control_message_init->type == TYPE1_CTRL_MSG_INITIATION) {
            send_hftp_message(sockfd, control_response_type1, &client);
            syslog(LOG_DEBUG, "Sent control message response (Type 1)");
            break;
        } else {
            syslog(LOG_DEBUG, "Message received from client, wrong type");
        }
    }

    memcpy(fileName, control_message_init->fileName, control_message_init->fileNameLength);

    // Add terminating null at end of file name
    fileName[control_message_init->fileNameLength+1] = '\0';
    //fileName[control_message_init->fileNameLength] = '-';
    
    fileSize = control_message_init->fileSize;
    
    syslog(LOG_INFO, "Received File %s (%d bytes)", fileName, fileSize);
    
    free(control_message_init);
    //free(control_response_type1);
    
    char fileFull[1460];
    memcpy(fileFull, dir, strlen(dir));
    //fileFull[strlen(dir)+1] = '\0';
    strcat(fileFull, "/");
    strcat(fileFull, fileName);

    FILE *fp;
    fp = fopen(fileFull, "w+" );

    int numberBytesWritten = 0;

    // Boolean flag for a file transfer taking place
    bool inTransfer = true;

    int control_type2_sequenceNumber = 0;

    int dataBlockNumber = 0;

    syslog(LOG_DEBUG, "Reading received file");
    
    while (inTransfer) {

        bool   waiting_data_message_s1 = true;
        while (waiting_data_message_s1) {
        
            data_message = (hftp_data_message*) receive_hftp_message(sockfd, &client);
            syslog(LOG_DEBUG, "Received data message");

            switch (data_message->type) {

                case TYPE1_CTRL_MSG_INITIATION: 					// 1
                    send_hftp_message(sockfd, control_response_type1, &client);
                    syslog(LOG_DEBUG, "Received control message (Type 1)");
                    break;
                case TYPE2_CTRL_MSG_TERMINATION: 					// 2
                    inTransfer = false;
                    control_type2_sequenceNumber = control_message_init->sequenceNumber;
                    syslog(LOG_DEBUG, "Received control message (Type 2)");
                    waiting_data_message_s1 = false;
                    break;
                case TYPE3_DATA_MSG:								// 3
                    if (data_message->sequenceNumber == 1) {
                        syslog(LOG_DEBUG, "Received data message, sequence 1");
                        
                        /* fwrite(
                        	array of elements to be written
                        	size of each element in bytes
                        	number of elements
                        	pointer to file stream
                        	)
                        */	
                         
                        numberBytesWritten += fwrite(
                                data_message->data,
                                sizeof(data_message->data[0]),
                                data_message->dataLength,
                                fp);
                                
                                
                        waiting_data_message_s1 = false;

                        data_message_ack = create_data_ack_message(data_message->sequenceNumber);
                        send_hftp_message(sockfd, data_message_ack, &client);
                        free(data_message_ack);
                        free(data_message);

                        dataBlockNumber++;
                    }
                    else if (data_message->sequenceNumber == 0) {
                        syslog(LOG_DEBUG, "Received data message, sequence 0");
                        data_message_ack = create_data_ack_message(data_message->sequenceNumber);
                        send_hftp_message(sockfd, data_message_ack, &client);
                        free(data_message_ack);
                        free(data_message);
                    }
                    break;
                default:
                    syslog(LOG_INFO, "Unsupported message received: %d", data_message->type);
                    exit(EXIT_FAILURE);
                    break;
            }
        }

        if (!inTransfer)
            break;
            
        bool waiting_data_message_s2 = true;
        
        while (waiting_data_message_s2) {
        
            data_message = (hftp_data_message*) receive_hftp_message(sockfd, &client);
            
            syslog(LOG_DEBUG, "Received data message");

            switch (data_message->type) {
            
                case TYPE3_DATA_MSG:								// 3
                    if (data_message->sequenceNumber == 0) {
                        
                        syslog(LOG_DEBUG, "Received data message, sequence 0");

                        numberBytesWritten += fwrite(
                                data_message->data,
                                sizeof(data_message->data[0]),
                                data_message->dataLength,
                                fp);

                        data_message_ack = create_data_ack_message(data_message->sequenceNumber);
                        send_hftp_message(sockfd, data_message_ack, &client);
                        free(data_message_ack);
                        free(data_message);

                        waiting_data_message_s2 = false;
                        
                        dataBlockNumber++;
                    }
                    else if (data_message->sequenceNumber == 1) {
                        
                        syslog(LOG_DEBUG, "Received data message, sequence 1");
                        
                        data_message_ack = create_data_ack_message(data_message->sequenceNumber);
                        send_hftp_message(sockfd, data_message_ack, &client);
                        free(data_message_ack);
                        free(data_message);
                        
                        waiting_data_message_s2 = false;
                    }
                    break;
                    
                case TYPE2_CTRL_MSG_TERMINATION:					// 2
                
                    inTransfer = false;
                    control_type2_sequenceNumber = control_message_init->sequenceNumber;
                    syslog(LOG_DEBUG, "Received control message (Type 2)");
                    break;
                default:
                    syslog(LOG_INFO, "Unsupported message received: %d", data_message->type);
                    exit(EXIT_FAILURE);
                    break;
            }
        }

		////// Percent of data sent
        if (dataBlockNumber > 6) {
        
            char buffer[100];
            sprintf(buffer, "Transmitted %d of %d bytes [%d complete]",
                             numberBytesWritten, fileSize,
                             (int)(((float)numberBytesWritten/(float)fileSize) * 100));
            syslog(LOG_INFO, "%s", buffer);
            dataBlockNumber = 0;
        }
    }

   char buffer[100];
            sprintf(buffer, "Transmitted %d of %d bytes [%d complete]",
                             numberBytesWritten, fileSize,
                             (int)(((float)numberBytesWritten/(float)fileSize) * 100));
            syslog(LOG_INFO, "%s", buffer);

    fclose(fp);

    syslog(LOG_DEBUG, "Server termination");
    
	// Type 2 control ACK here
    hftp_message* control_messageerm = create_type2_control_ack_response(control_type2_sequenceNumber);
    send_hftp_message(sockfd, control_messageerm, &client);
    
    // Close the socket
    close(sockfd);

    syslog(LOG_INFO, "File transferred successfully");

    exit(EXIT_SUCCESS);
}


