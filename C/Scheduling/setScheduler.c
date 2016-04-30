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
 *		$ ./setscheduler <FIFO, OTHER, or RR> ./<executable>
 *
 * setScheduler.c sets the scheduling policy for the process that is passed to it as 
 * an executable. 
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and setting the 
 * scheduling policy for the process that is to be forked.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: ./setscheduler <OTHER, FIFO, or RR> ./<executable>\n");
    } else {

        pid_t pid;
        int i;

        int policy;
        struct sched_param param;

        // get the user specified schedule type and set it
        if (!strcmp(argv[1], "FIFO")) {
            policy = SCHED_FIFO;
        } else if (!strcmp(argv[1], "RR")) {
            policy = SCHED_RR;
        } else {
            policy = SCHED_OTHER;
        }

        /* set process to max priority for given scheduler */
        param.sched_priority = sched_get_priority_max(policy);

        // fork to run new process with the designated schedule type
        pid = fork();
        if (pid < 0) {
            perror("fork()");
            exit(EXIT_FAILURE);
        }
        // parent process
        if (pid > 0) {
            wait(NULL);
        } else {
            // assign schedule type to child process
            if (sched_setscheduler(pid, policy, & param)) {
                perror("Error setting scheduler policy");
                exit(EXIT_FAILURE);
            }
            // select the arguments for executing a program
            char **cmd = argv + 2;

            // execute the program with schedule type
            execvp(cmd[0], cmd);
        }
    }
}