/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 7, 2015
 * checksums.c is a supporting class for client that contains the functions to compute the checksum of a passed file with the crc32 hash
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "checksums.h"

/*
 * checksum method
 * This method returns the crc32 checksum for the passed file in an unsigned integer format
 * Input parameters:
 f - The path to the file to get the checksum for
 * Output: An unsigned integer of the crc32 checksum for that file
 */
unsigned int checksum(char *f) {
    // declare a string for the character buffer
    unsigned char *buffer;
    // declare an integer variable for the files size
    unsigned long fileSize;
    // declare an integer for the crc hash return value
    unsigned int crc;
    // get the size of the file in bytes
    fileSize = getSize(f);
    // get the string buffer of the file contents
    buffer = getBuffer(fileSize, f);
    // original crc32 checksum (null)
    crc = crc32(0L, Z_NULL, 0);
    // get the crc32 checksum of the buffer
    crc = crc32(crc, buffer, fileSize);
    // free the buffer from memory
    free(buffer);
    // return the integer hash
    return crc;
}

/*
 * getBuffer method
 * This method returns the string buffer of the input file
 * Input parameters:
        s - The size of the file input in bytes
        f - The path to the input file to read in
 * Output: A unsigned string containing the contents of the file
 */
unsigned char* getBuffer(unsigned long s, char *f) {
    // open the file passed for binary reading
    FILE *inFile = openRB(f);
    // declare a string for the character buffer
    unsigned char *bufferString;
    // allocate enough space for the file size in the buffer
    bufferString = malloc(s);
    // read all the bytes into the buffer from the input file
    if (bufferString) {
        fread(bufferString, 1, s, inFile);
    }
    // close the input file
    fclose(inFile);
    // error message if the buffer ran out of memory while reading in bytes
    if(bufferString == NULL) {
        fprintf(stderr, "Error: Unable to reserve enough memory for the file buffer\n");
        // failure exit code if buffer ran out of memory
        exit(EXIT_FAILURE);
    }
    else {
        // return the string buffer of the file contents
        return bufferString;
    }
}

/*
 * getSize method
 * This method returns the size of the file input in bytes
 * Input parameters:
        f - The path to the input file to read in
 * Output: A unsigned integer of the file size in bytes
 */
unsigned long getSize(char *f) {
    // open the file passed for binary reading
    FILE *inFile = openRB(f);
    unsigned long sizeFile;
    // seek to the end of the opened file to find its size
    fseek(inFile, 0, SEEK_END);
    sizeFile = ftell(inFile);
    // seek back to the beginning of the file
    fseek(inFile, 0, SEEK_SET);
    // close the input file
    fclose(inFile);
    // give an error message if there were no contents in the file
    if(sizeFile == 0) {
        fprintf(stderr, "Error: File %s had a size of 0\n", f);
        // exit failure if the file had nothing in it
        exit(EXIT_FAILURE);
    }
    else {
        // return the size of the file in bytes
        return sizeFile;
    }
}

/*
 * openRB method
 * This method returns a pointer to the opened FILE passed as a parameter
 * Input parameters:
        f - The path to the input file to read in
 * Output: A FILE pointer to be modified and read in later
 */
FILE* openRB(char *f) {
    // declare a FILE pointer in for the input file
    FILE *inFile;
    // open the file passed as parameter to the in FILE pointer
    inFile = fopen(f, "rb");
    // if the file pointer remains null, the file could not be opened
    if (inFile == NULL) {
        // error message for the unopened file
        fprintf(stderr, "Error: Could not open file %s\n", f);
        // exit code for failure
        exit(EXIT_FAILURE);
    }
    else {
        // return the FILE pointer
        return inFile;
    }
}
