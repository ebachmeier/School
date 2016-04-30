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
 *		$ ./kernelinfo
 *
 * kernelInfo.c retrieves the information about the processor type and kernel version
 * for the user using /proc/cpuinfo and /proc/version files.
 */

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 3, 2016
 * Purpose: This is the main method for argument error detection and accessing the
 * requires files to display the information lines to the user.
 * Input Parameters:
 * 		argv - arguments from the command-line
 * Output: Integer return status
 */
int main(){

    FILE *fd = fopen("/proc/cpuinfo", "r" );
    char buffer[BUFFER_SIZE];
    char *vendorActual = NULL, *modelActual = NULL;
   	const char vendor[10] = "vendor_id";
   	const char model[7] = "model ";

    if(fd == NULL) {
        fprintf( stderr, "Unable to open file cpuinfo\n" );
    }
    else {
    
        // Read each line into the buffer
        while(fgets(buffer, BUFFER_SIZE, fd) != NULL ) {
        
        	// See if the line stored contains the vendor name
        	vendorActual = strstr(buffer, vendor);
        	if (vendorActual != NULL) {
        		printf("%s", vendorActual);
        	}
        	
        	// See if the line stored contains the model name
        	modelActual = strstr(buffer, model);
        	if (modelActual != NULL) {
        		printf("%s", modelActual);
        	}
        }
        fclose(fd);        
	}
	
	fd = fopen("/proc/version", "r" );
    char *version = NULL;
    
    if(fd == NULL) {
        fprintf( stderr, "Unable to open file version\n" );
    }
    else {
    
    	printf("version         : ");
        // Read each line into the buffer
        while(fgets(buffer, BUFFER_SIZE, fd) != NULL ) {
        	version = strtok(buffer, "(");
        	printf("%s\n", version);
        }
        fclose(fd);        
	}
    
    return 0;
}