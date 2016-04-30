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
 *		$ ./observer ./executablefilehere
 *
 * observer.c monitors a process passed as a command-line argument and shows the amount
 * of time the process is scheduled in user and kernel mode. This is done every second 
 * by reading from the /proc/pid/stat file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
#include <unistd.h>
#include <math.h>

#define BUFFER_SIZE 1024

/*
 * execute method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This method executes the passed child process and reads from the stat file
 * every second until the child process is terminated.
 * Input Parameters:
 * 		argv - the array of arguments passed to the program including the executable to
 *				run.
 * Output: None
 */
void execute(char **argv) {

    pid_t pid;
    int status;

	// fork a child process
    if ((pid = fork()) < 0) {
    	printf("Error: forking a child process failed\n");
        exit(1);
    }
    else if (pid == 0) {
    	// execute the program
        if (execvp(argv[1], argv) < 0) {
            printf("Error: exec %s failed\n", argv[1]);
            exit(1);
        }
    }
    else {
    	printf("PID = %ld\n", (long)pid);
        char filename[20];
		sprintf(filename, "/proc/%ld/stat", (long)pid);	
		
		while(1) {
		
        	unsigned long user;
        	unsigned long kernel;
        	char buffer[BUFFER_SIZE];
        	FILE *fd;
        	if (!(fd = fopen(filename, "r"))) printf("Unable to open stat file for pid = %ld\n", (long)pid);
        	
        	fscanf(fd, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu", &user, &kernel);
        	printf("User mode for %lu\t\t", user);
        	printf("Kernel mode for %lu\n", kernel);
    		fclose(fd);
    		
			sleep(1);
		}
	}
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and making a call to 
 * execute the process.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(int argc, char *argv[]) {

   	if( argc != 2 ) {
      	printf("Usage: ./observer ./<executable>\n");
   	}
   	else {
      	// execute the program
     	execute(argv);
   	}
}