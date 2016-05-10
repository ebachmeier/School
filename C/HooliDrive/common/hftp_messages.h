#ifndef HFTP_MESSAGES_H
#define HFTP_MESSAGES_H

#define ACK_TYPE0_SEND   0
#define ACK_TYPE1_ACK    1

#define TYPE1_CTRL_MSG_INITIATION  1
#define TYPE2_CTRL_MSG_TERMINATION 2
#define TYPE3_DATA_MSG             3

#define SEQUENCE_0       0
#define SEQUENCE_1       1

typedef struct {
	int length;
	uint8_t buffer[1472];
} hftp_message;

typedef struct
{
	int length;
 	uint8_t type;                
	uint8_t ack;        
	uint16_t sequenceNumber;  
	uint32_t fileSize;         
	uint32_t fileNameLength;
	//uint32_t checksum;
	//uint8_t token[16];			// 16 byte token
	uint8_t fileName[1460];	/////// 1440
} hftp_control_message;

typedef struct
{
	int length;
 	uint8_t type;                
	uint8_t ack;        
	uint16_t sequenceNumber;           
	uint32_t dataLength;
	uint8_t data[1464];
} hftp_data_message;

hftp_message* create_hftp_message();

hftp_message* receive_hftp_message(int sockfd, host* source);

hftp_message* receive_hftp_message_with_timeout(int sockfd, int timeout, host* source);

int send_hftp_message(int sockfd, hftp_message* msg, host* dest);

hftp_message* create_control_message(uint8_t type, uint8_t ack, uint16_t sequenceNumber,
									   	uint32_t fileSize, uint32_t fileNameLen,
									   	uint32_t* fileName);

hftp_message* create_data_message(uint8_t ack, uint16_t sequenceNumber, 
										uint32_t dataLen, uint32_t* data);


#endif