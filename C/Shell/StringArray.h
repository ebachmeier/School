/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * Janurary 20, 2016
 * 
 * StringArray.h is the header file with definitializeions for StringArray.c
 */
 
#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "StringQueue.h"

typedef struct StringArray {
    int size;
    int count;
    int start, end;
    // pointer to an array of pointers
    char*** elem;
} StringArray;

StringArray* initializeStringArray(int size);
char** topStringArray(StringArray* qHist);
char** dequeueStringArray(StringArray* qHist);
char** getStringArrayElement(StringArray* qHist, int index);
void enqueueStringArray(StringArray* qHist, char** tokens);
void freeStringArrayData(StringArray* qHist);
void printStringArray(StringArray* qHist);

#endif