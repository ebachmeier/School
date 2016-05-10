/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 3
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * March 17, 2016
 *
 * To compile and run:
 * 		$ make
 *		$ ./server 5555 3
 *                 port num_threads
 *
 * server.c handles multiple client connections using threads.
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <pthread.h>
#include <netdb.h>
#include <semaphore.h>

#define MAX_MSG_SIZE 1024
#define BACKLOG 20

// struct to store a connection in the queue
typedef struct client_connection {
	int connfd;
	struct client_connection* next;
} client_connection;

static bool term_requested = false;
client_connection* head = NULL;
client_connection* back = NULL;
int queue_length = 0;
sem_t q, mutex;
pthread_t* threads;
//pthread_barrier_t barr;

/*
 * term_handler method
 * Author: Eric Bachmeier
 * Created: March 17, 2016
 * Purpose: This function is the handler for the termination flag for this server.
 * Input Parameters:
 *		signal - the flag which is global
 * Output: None
 */
void term_handler(int signal) {
    printf("Server termination requested\n");
    term_requested = true;
}

/*
 * enqueue method
 * Author: Eric Bachmeier
 * Created: March 18, 2016
 * Purpose: This function is used to add a connection to the connection queue.
 * Input Parameters:
 *		newfd - new connection to be added to the queue
 * Output: None
 */
void enqueue(int newfd) {

	client_connection* new_connection = (client_connection*) malloc(sizeof(client_connection));
	new_connection->connfd = newfd;
	new_connection->next = NULL;
	
	if (head == NULL) {
		back = head = new_connection;
	} else if (head == back) {
		back = new_connection;
		head->next = back;
	} else {
		back->next = new_connection;
		back = new_connection;
	}
	
	queue_length++;
}

/*
 * dequeue method
 * Author: Eric Bachmeier
 * Created: March 18, 2016
 * Purpose: This function is used to remove a connection to the connection queue.
 * Input Parameters: None
 * Output: Returns the connection dequeued
 */
int dequeue() {

	client_connection* temp = head;
	int retfd;
	
	if(head == NULL) {
		return '\0';
	} 
	
	retfd = temp->connfd;
	
	if (head == back) {
		head = back = NULL;
	} else {
		head = head->next;
	}
	
	queue_length--;
	free(temp);
	
	return retfd;
}

/*
 * handle_connection method
 * Author: Eric Bachmeier
 * Created: March 17, 2016
 * Purpose: This function receives a number from the client and multiplies it by 10.
 * Input Parameters:
 *		connfd - A open connection to a client
 * Output: This function sends back the product to the client
 */
void* handle_connection(void* arg) {

	int connfd, product, numbytes;
    char recvBuff[MAX_MSG_SIZE], sendBuff[MAX_MSG_SIZE];
	
	while(1) {
	
		// block while no connections exist in the queue
		sem_wait(&q);
		
    	memset(recvBuff, '0', sizeof(recvBuff));
		memset(sendBuff, '0', sizeof(sendBuff));
		
		// get a waiting connection from queue
		sem_wait(&mutex);
		connfd = dequeue();
		sem_post(&mutex);
		
		// receive number message from the client
		numbytes = recv(connfd, recvBuff, sizeof(recvBuff) - 1, 0);
		if (numbytes == -1) {
			perror("recv");
			exit(1);
		}
		recvBuff[numbytes] = '\0';
		
		// calculate the product of the received number and 10
		product = atoi(recvBuff) * 10;
	
		// send the product back to the client
		snprintf(sendBuff, sizeof(sendBuff), "%d", product);
		send(connfd, sendBuff, strlen(sendBuff), 0);
		
		// close the connection with the client
		close(connfd);
    }
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 17, 2016
 * Purpose: This function is the main method for executing the server. It takes input from
 * the command-line for the port number to listen on and the number of threads to create.
 * Input Parameters: None
 * Output: Integer status for the exit code
 */
int main(int argc, char* argv[]) {

    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    int i, num_threads;

    // parse the command-line input for the port number to listen on
    if (argc != 3) {
        printf("\n\tUsage: %s port num_threads\n\n", argv[0]);
        return 1;
    }

	// set the maximum number of threads at a time
	num_threads = atoi(argv[2]);
	
	// create a listening socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Error in socket creation");
        exit(1);
    }
    
    // specify the listening socket
    memset( & serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

	// bind the listening socket
    if (bind(listenfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    // listen on this socket for incoming connections
    listen(listenfd, BACKLOG);

	// initialize semaphores
	sem_init(&q,0,0);
	// mutex gets value of 1
	sem_init(&mutex,0,1);
	
	// launch thread pool
	threads = malloc(num_threads * sizeof(pthread_t));
	
	for(i = 0; i < num_threads; i++) {
		pthread_create(&threads[i], NULL, handle_connection, (void*) NULL);
	}
	
    // wait to accept a connection and process it
    while (!term_requested) {
        // wait for connection and handle it
        connfd = accept(listenfd, (struct sockaddr * ) NULL, NULL);
        
        // when a connection arrives, add it to the queue
        sem_wait(&mutex);
        enqueue(connfd);
        sem_post(&mutex);
        
        // wake up a blocked thread
        sem_post(&q);
    }

    // close the socket
    close(listenfd);

    // exit the program successfully 
    exit(0);
}