/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 7, 2015
 * files.h is the header file with function prototypes for files.c
 */

#ifndef files_h
#define files_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

// Function to traverse a file tree
void searchDirectory(char *name, char *prev, FILE *outfile);

// Function to save a node of the filename and checksum
void saveFileCheck(char *n, char *p, char *s, FILE *outfile);

#endif
