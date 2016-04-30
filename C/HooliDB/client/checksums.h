/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 7, 2015
 * checksums.h is the header file with function prototypes for checksums.c
 */

#ifndef checksums_h
#define checksums_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

unsigned int checksum(char *f);
FILE* openRB(char *f);
unsigned long getSize(char *f);
unsigned char* getBuffer(unsigned long s, char *f);

#endif /* checksums_h */
