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
 *		$ ./comparison2
 *
 * comparison2.c simulates a process that sits idle until an event occurs. The program 
 * sleeps for one second and then calls a I/O intensive function.
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
 * iointensive method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the method that is intensive for file I/O and will not require CPU
 * resources while running.
 * Input Parameters: None
 * Output: None
 */
void iointensive(void) {

	FILE *fd = fopen("list", "w");
	
  	double i = 0.01;
  	while (i < MAXNUM) {
    	system("od list > newfile");
    	i += 0.01;
  	}
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and calling the sleep 
 * and I/O intensive functions infinitely.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(int argc, char** argv) {

	signal(SIGINT, int_handler);

  	while (1) {
      	sleep(1);
      	iointensive();
  	}
	exit(EXIT_SUCCESS);
}


