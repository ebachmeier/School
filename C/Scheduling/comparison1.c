/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 2
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * March 3, 2016
 *
 * To compile and run:
 * 		$ make
 *		$ ./comparison1
 *
 * comparison1.c simulates a process that sits idle until an event occurs. The program 
 * sleeps for one second and then calls a cpu intensive function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MAXNUM 1000

/* Interrupt handler */
void int_handler(int sig) {
  	signal(sig, SIG_IGN);
  	exit(EXIT_SUCCESS);
}

/*
 * cpuintensive method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the method that is cpu intensive and will require a lot of CPU 
 * resources while running.
 * Input Parameters: None
 * Output: None
 */
void cpuintensive(void) {
  	double x = 0.01;
  	while(x <= MAXNUM) {
    	x += 0.01;
  	}	
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and calling the sleep 
 * and cpu intensive functions infinitely.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(int argc, char** argv) {

	signal(SIGINT, int_handler);

  	while (1) {
      	sleep(1);
      	cpuintensive();
  	}
	exit(EXIT_SUCCESS);
}


