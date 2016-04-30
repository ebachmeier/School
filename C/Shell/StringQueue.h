/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * Janurary 20, 2016
 * 
 * StringQueue.h is the header file with definitializeions for StringQueue.c
 */
 
#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 256

typedef struct StringQueue {
    int size;
    int count;
    int start, end;
    // this is a pointer to an array of characters
    char (*history)[MAX_CHARS];
} StringQueue;

StringQueue*  initializeStringQueue(int size);
char* topStringQueue(StringQueue* qHist);
char* dequeueString(StringQueue* qHist);
void enqueueString(StringQueue* qHist, char* msg);
void freeStringQueueData(StringQueue* qHist);
int stringQueueCount(StringQueue* qHist);
void printStringQueue(StringQueue* qHist, int n);

#endif
