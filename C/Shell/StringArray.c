/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * Janurary 20, 2016
 *
 * StringArray.c is the file containing functions for storing an array of command symbols
 * and operands
 */

#include "StringArray.h"

/*
 * initializeStringArray method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method initializes and allocates memory for an array of strings with
 * 			a specified size
 * Input Parameters:
 * 		size - the length of string array to initialize
 * Output: The array that was created
 */
StringArray* initializeStringArray(int size) {
    StringArray* s = (StringArray*)malloc(sizeof(StringArray));
    s->size = size;
    s->start = 0;
    s->end = -1;
    s->count = 0;
    s->elem = malloc(size * sizeof(s->elem[0]));
    return s;
}

/*
 * freeStringArrayData method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method resets and frees memory that was allocated previously
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: None
 */
void freeStringArrayData(StringArray* qHist) {
    for (int i = 0; i < qHist->count; i++) {
        free(qHist->elem[i]);
    }
    free(qHist->elem);
    qHist->count = 0;
    qHist->start = 0;
    qHist->end = -1;
}

/*
 * getStringArrayElement method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method retrieves a specific indexed string element from the history array
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 *		index - the index of the element to get
 * Output: A pointer to a char that contains the element
 */
char** getStringArrayElement(StringArray* qHist, int index) {
    return qHist->elem[index];
}

/*
 * topStringArray method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method returns the starting element in the previous commands array
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: A pointer to a char that contains the first element
 */
char** topStringArray(StringArray* qHist) {
    return qHist->elem[qHist->start];
}

/*
 * dequeueStringArray method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method removes the starting element from the array
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: The new array copy if successful, otherwise NULL
 */
char** dequeueStringArray(StringArray* qHist) {

    if (qHist->count > 0) {
        char** tokens = qHist->elem[qHist->start];
        qHist->start = (qHist->start + 1) % qHist->size;
        qHist->count--;
        return tokens;
    }
    else {
        return NULL;
    }
}

/*
 * enqueueStringArray method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method adds an addition queueing spot to the StringArray
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: None
 */
void enqueueStringArray(StringArray* qHist, char** tokens) {
    qHist->end = (qHist->end + 1) % qHist->size;
    if (qHist->end == qHist->start && qHist->count >= qHist->size) {
        qHist->start = (qHist->end+1)%qHist->size;
    }
    if (qHist->count < 10) {
        qHist->count++;
    }
    qHist->elem[qHist->end] = tokens;
}

/*
 * printStringArray method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method prints the entire list of commands to the screen for the user
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: None
 */
void printStringArray(StringArray* qHist) {

    for (int i = 0; i < qHist->count; i++) {
        printf("[%d]: ", i);
        int j = 0;
        while (qHist->elem[i][j] != NULL) {
            printf("%s", qHist->elem[(qHist->start+i)%qHist->size][j]);
            j++;
        }
        printf("\n");
    }
}
