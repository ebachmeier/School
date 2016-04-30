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
 *		$ ./compare
 *
 * compare.c calculates the time it takes to make a minimal function call and a minimim
 * system call.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BILLION  1000000000L

#define CLOCK_ID CLOCK_PROCESS_CPUTIME_ID

/* Compute the difference between two time stamps returned by clock_gettime */
uint64_t diff(struct timespec start, struct timespec end)
{
  uint64_t diff;

  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

  return diff;
}

int simpleFunction() {
}

/*
 * main method
 * Author: Eric Bachmeier & Hanan Lutfiyya
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and computing two 
 * elapsed times for a minimal function and getting the PID.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(int argc, char *argv[]) {
  struct timespec start, end;
  uint64_t elapsedTime;
  pid_t p;
  clock_gettime(CLOCK_ID, &start);
     
  simpleFunction();     

  clock_gettime(CLOCK_ID, &end);
  
  elapsedTime = diff(start,end);
  
  printf("minimal function took %llu\n",(long long unsigned int) elapsedTime);
  
  clock_gettime(CLOCK_ID, &start);
     
  p = getpid();     

  clock_gettime(CLOCK_ID, &end);
  
  elapsedTime = diff(start,end);
  
  printf("process identifier took %llu\n",(long long unsigned int) elapsedTime);

}
