
/********************************************************************************
* rftp.c
*
* Computer Science 3357a
* Assignment 2
*
* Author: Dustin Dobransky, 250575030, ddobran <at> uwo.ca
*
* The client for the reliable FTP program.
*
* Half baked.  Works, but lacks proper style, commenting, and design.
* Too many other final projects in the way to properly polish things.
* Will resubmit a cleaner copy if allowed to, please let me know.
* Thanks,
*     Dustin
*     
*******************************************************************************/
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "udp_sockets.h"
#include "udp_server.h"
#include "udp_client.h"
#include <stdbool.h>
#include <syslog.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include "rftp_messages.h"

/*
When the client wants to initiate a transfer, it sends a type 1 control
message (initiation message) to the server. The sequence number of this
initial message is always 0.
*/
rftp_control_message_t* create_type1_control_message(char** filename, int fileSize) {
    rftp_control_message_t* msg = (rftp_control_message_t*) create_rftp_message();
    msg->ack = ACK_TYPE0_SEND;
    msg->type = TYPE1_CTRL_MSG_INITIATION;
    msg->sequenceNumber = 0;

    memcpy(msg->fileName, *filename, strlen(*filename));
    msg->fileNameLength = strlen(*filename);

    msg->fileSize = fileSize;

    syslog(LOG_DEBUG, "fileNameLength: %d", msg->fileNameLength);

    // sizeof(type) + sizeof(ack) + ... + sizeof(fileNameLength) + 
    // sizeof(filename)
    msg->length = 12 + strlen(*filename);

    return msg;
}

//To ACK the message, the server responds with a type 1 control
//message of its own, setting the ACK field to 1 and the Sequence
//Number field to 0. The rest of the fields are left empty.
bool is_type1_ack_message(rftp_message_t* msg) {
    rftp_control_message_t* _msg = (rftp_control_message_t*) msg;
    return (_msg->type == 1 && _msg->ack == 1 && _msg->sequenceNumber == 0);
}

//To ACK the termination message, the server responds with a type 2
//control message, setting the ACK field 1 and the Sequence Number
//field to the sequence number of the received termination message.
bool is_type2_ack_message(rftp_message_t* msg, int expectedSeqNum) {
    rftp_control_message_t* _msg = (rftp_control_message_t*) msg;
    return (_msg->type==2 &&
            _msg->ack == 1 &&
            _msg->sequenceNumber == expectedSeqNum);
}

void getOptions(int argc, char** argv, int* timeout, char** port) {
    int c;
    //bool verbose = false;

    // parse the command line arguments: port, math expression, and server
    while (true) {
        static struct option long_options[] =
        {
            {"verbose", required_argument, 0, 'v'},
            {"timeout", required_argument, 0, 't'},
            {"port", required_argument, 0, 'p'},
            {0, 0, 0, 0}
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "vt:p:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 'p':
                *port = optarg;
                syslog(LOG_DEBUG, "Listening on port: %s", *port);
                break;
            case 't':
                *timeout = atoi(optarg);
                syslog(LOG_DEBUG, "Timeout: %d", *timeout);
                break;
            case 'v':
                //verbose = true;
                setlogmask(LOG_UPTO(LOG_DEBUG));
                syslog(LOG_DEBUG, "Verbose flag set");
                break;
            case '?':
                break;
        }
    }
}

void getNonOptions(char** serverIp, char** filename, int optind, int argc, char** argv) {
    syslog(LOG_DEBUG, "argc: %d, optind: %d", argc, optind);
    if (argc-optind != 2) {
        syslog(LOG_DEBUG, "Server or filename not specified!");
        exit(EXIT_FAILURE);
    }
    *serverIp = argv[optind];
    *filename = argv[optind+1];
    syslog(LOG_DEBUG, "serverIp: %s, filename: %s, fileNameLength: %d", *serverIp, *filename, (int)strlen(*filename));
}

int main(int argc, char** argv) {

    openlog("rftp", LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    setlogmask(LOG_UPTO(LOG_DEBUG));
    syslog(LOG_DEBUG, "START CLIENT");

    int   timeout = 0;
    char* port    = NULL;
    char* serverIp  = NULL;
    char* filename = NULL;

    getOptions(argc, argv, &timeout, &port);
    getNonOptions(&serverIp, &filename, optind, argc, argv);

    syslog(LOG_DEBUG, "s: %s, p: %s, f: %s", serverIp, port, filename);

    if (port == NULL || serverIp == NULL || filename == NULL) {
        syslog(LOG_DEBUG, "must supply valid arguments");
        exit(EXIT_FAILURE);
    }
    syslog(LOG_DEBUG, "Args accepted");

    FILE* fp;
    fp = fopen(filename, "r");

    rftp_control_message_t* type1AckMsg;
    rftp_data_message_t*    dataAckMsg;
    host_t server;    // Client's address

    // Create a socket to listen on port 5000
    int sockfd;
    sockfd = create_client_socket(serverIp, port, &server);

    syslog(LOG_DEBUG, "socket created");

    // create type1 control message
    // Message read from the client
    int fileSize = 0;
    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    syslog(LOG_DEBUG, "fileSize: %d", (int)fileSize);
    rftp_control_message_t* type1CtrlMsg = create_type1_control_message(&filename, fileSize);

    int lastSequenceNum = SEQUENCE_0;

    bool hasTimedout = true;
    while (hasTimedout) {
        // send type 1 control message
        syslog(LOG_DEBUG, "send_rftp_message: type1CtrlMsg");
        send_rftp_message(sockfd, (rftp_message_t*)type1CtrlMsg, &server);

        type1AckMsg = (rftp_control_message_t*) receive_rftp_message_with_timeout(sockfd, timeout, &server);
        syslog(LOG_DEBUG, "receive_rftp_message: type1CtrlMsgACK");

        if (type1AckMsg != NULL) {

            if (type1AckMsg->ack == ACK_TYPE1_ACK) {
                hasTimedout = false;
                free(type1CtrlMsg);
                free(type1AckMsg);
                syslog(LOG_DEBUG, "ACK_TYPE1_ACK - good");
            } else {
                syslog(LOG_DEBUG, "type1 ack not received - not good");
            }
        } else {
            hasTimedout = true;
            syslog(LOG_DEBUG, "timeout - resending type1CtrlMsg");

            //puts("No message received in 10s.  Exiting.");
        }
    }
    //free(type1CtrlMsg);

    syslog(LOG_DEBUG, "Begin File Transfer");

    /*Begin file transfer*/


    if (fp == NULL) {
        syslog(LOG_DEBUG, "Unable to open file");
        exit(EXIT_FAILURE);
    }

    lastSequenceNum = SEQUENCE_1;

    int co = 0;

    do {
        syslog(LOG_DEBUG, "Step 1");

        /*Construct data message*/
        rftp_data_message_t* dataMsg = (rftp_data_message_t*) create_rftp_message();

        dataMsg->dataLength = 
            fread(
                dataMsg->data, // pointer to a block of memory with a minimum size of size*nmemb bytes.
                sizeof(dataMsg->data[0]), //size in bytes of each element to be read.
                sizeof(dataMsg->data) / sizeof(dataMsg->data[0]), // number of elements, each one with a size of size bytes.
                fp); // pointer to a FILE object that specifies an input stream.
        
        dataMsg->type = TYPE3_DATA_MSG;
        dataMsg->ack = ACK_TYPE0_SEND;
        dataMsg->sequenceNumber = SEQUENCE_1;

        syslog(LOG_DEBUG, "dataMsg->dataLength SEQ1: %d", dataMsg->dataLength);

        dataMsg->length = 8 + dataMsg->dataLength;

        /* Type 1 ACK received
        send first data message */
        hasTimedout = true;
        while (hasTimedout) {
            // send type 1 control message
            send_rftp_message(sockfd, (rftp_message_t*)dataMsg, &server);
            syslog(LOG_DEBUG, "Sent dataMsg");

            dataAckMsg = (rftp_data_message_t*) receive_rftp_message_with_timeout(sockfd, timeout, &server);
            syslog(LOG_DEBUG, "Received data ack msg");

            if (dataAckMsg != NULL) {
                if (dataAckMsg->ack == ACK_TYPE1_ACK) {
                    hasTimedout = false;
                    free(dataAckMsg);
                    lastSequenceNum = SEQUENCE_1;
                    syslog(LOG_DEBUG, "ACK1 == OK");
                } else {
                    syslog(LOG_DEBUG, "ack not ACK1");
                }
            } else {
                // if hasTimedout, then retransmit message
                hasTimedout = true;
                syslog(LOG_DEBUG, "Timedout, retransmit data msg");
                //puts("No message received in 10s.  Exiting.");
            }
        }
        free(dataMsg);

        if (feof(fp))
            break;  

        syslog(LOG_DEBUG, "Step 2");

        dataMsg = (rftp_data_message_t*) create_rftp_message();
        dataMsg->dataLength = 
            fread(
                dataMsg->data, // pointer to a block of memory with a minimum size of size*nmemb bytes.
                sizeof(dataMsg->data[0]), //size in bytes of each element to be read.
                sizeof(dataMsg->data) / sizeof(dataMsg->data[0]), // number of elements, each one with a size of size bytes.
                fp); // pointer to a FILE object that specifies an input stream.
        
        dataMsg->type = TYPE3_DATA_MSG;
        dataMsg->ack = ACK_TYPE0_SEND;
        dataMsg->sequenceNumber = SEQUENCE_0;
        syslog(LOG_DEBUG, "dataMsg->dataLength SEQ0: %d", dataMsg->dataLength);

        dataMsg->length = 8 + dataMsg->dataLength;

        /* Type 0 ACK received
        send first data message */
        hasTimedout = true;
        while (hasTimedout) {
            // send type 1 control message
            send_rftp_message(sockfd, (rftp_message_t*)dataMsg, &server);

            dataAckMsg = (rftp_data_message_t*) receive_rftp_message_with_timeout(sockfd, timeout, &server);

            if (dataAckMsg != NULL) {
                if (dataAckMsg->ack == ACK_TYPE1_ACK) {
                    hasTimedout = false;
                    free(dataAckMsg);
                    lastSequenceNum = SEQUENCE_0;
                    syslog(LOG_DEBUG, "ACK0 == OK");
                } else {
                    syslog(LOG_DEBUG, "NOT ACK 0 - bad");
                    co++;
                    if (co > 10) {
                        exit(EXIT_FAILURE);
                    }
                }
            } else {
                // if hasTimedout, then retransmit message
                hasTimedout = true;
                syslog(LOG_DEBUG, "Timedout, retransmit data msg");
                //puts("No message received in 10s.  Exiting.");
            }
        }
        free(dataMsg);

        /*Construct next data packet*/
    } while (!feof(fp));

    /*Send type 2 control message*/
    rftp_control_message_t* type2CtrlMsg = (rftp_control_message_t*) create_rftp_message();
    type2CtrlMsg->type = TYPE2_CTRL_MSG_TERMINATION;
    type2CtrlMsg->sequenceNumber = lastSequenceNum == SEQUENCE_0 ? SEQUENCE_1 : SEQUENCE_0;
    type2CtrlMsg->ack = ACK_TYPE0_SEND;
    type2CtrlMsg->length = 8;

    syslog(LOG_DEBUG, "created type2CtrlMsg for termination");

    rftp_control_message_t* type2AckMsg;

    hasTimedout = true;
    while (hasTimedout) {
        // send type 2 control message
        send_rftp_message(sockfd, (rftp_message_t*)type2CtrlMsg, &server);

        type2AckMsg = (rftp_control_message_t*) receive_rftp_message_with_timeout(sockfd, timeout, &server);

        if (type2AckMsg != NULL) {
            if (type2AckMsg->ack == ACK_TYPE1_ACK) {
                hasTimedout = false;
                syslog(LOG_DEBUG, "ACK1 == OK");
            }
        } else {
            hasTimedout = true;
            syslog(LOG_DEBUG, "Timedout, retransmit data msg");
            //puts("No message received in 10s.  Exiting.");
        }
    }
    free(type2CtrlMsg);

    // Close the socket
    close(sockfd);

    syslog(LOG_DEBUG, "File transferred successfully");

    exit(EXIT_SUCCESS);
}
