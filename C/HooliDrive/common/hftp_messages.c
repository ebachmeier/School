/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 3
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * November 30, 2015
 * hftp_messages.c contains functions and definitions for file transfer with UDP
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include "udp_sockets.h"
#include "hftp_messages.h"

hftp_message* create_hftp_message() {
	return (hftp_message*) malloc(sizeof(hftp_message));
}

hftp_message* receive_hftp_message(int sockfd, host* source) {
	hftp_message* msg = create_hftp_message();
  	source->addr_len = sizeof(source->addr);
  	msg->length = recvfrom(sockfd, msg->buffer, sizeof(msg->buffer), 0,                  
    	(struct sockaddr*)&source->addr,                           
        &source->addr_len);

  	if (msg->length > 0) {
    	inet_ntop(source->addr.sin_family, &source->addr.sin_addr,                  
        	source->friendly_ip, sizeof(source->friendly_ip));                  
    	return msg;                                                               
  	}
  	else {
   		free(msg);                                                               
    	return NULL;                                                               
  	}
}

hftp_message* receive_hftp_message_with_timeout(int sockfd, int timeout, host* source) {

	hftp_message* msg;   	// Message read from the client
    int retval;       		// Return value from poll

    struct pollfd fd = {
        .fd = sockfd,
        .events = POLLIN
    };

    // Poll the socket for timeout seconds
    retval = poll(&fd, 1, timeout);

    if (retval == 1 && fd.revents == POLLIN) {
        // Read the waiting message
        msg = receive_hftp_message(sockfd, source);
        return msg;
    } 
    else {
        return NULL;
    }
}

int send_hftp_message(int sockfd, hftp_message* msg, host* dest) {
  	return sendto(sockfd, msg->buffer, msg->length, 0,
    	(struct sockaddr*)&dest->addr, dest->addr_len);
}


hftp_message* create_control_message(uint8_t type, uint8_t ack, uint16_t sequenceNumber,
									   uint32_t fileSize, uint32_t fileNameLen,
									   uint32_t* fileName) {
									   
	hftp_control_message* msg = (hftp_control_message*) create_hftp_message();

	return (hftp_message*) msg;
}

hftp_message* create_data_message(uint8_t ack, uint16_t sequenceNumber,
									uint32_t dataLen, uint32_t* data) {
									
	hftp_data_message* msg = (hftp_data_message*) create_hftp_message();
    
	return (hftp_message*) msg;
}