/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * Janurary 20, 2016
 *
 * StringQueue.c is the file containing the methods for initializing, using, and freeing
 * a queue of strings containing commands
 */

#include "StringQueue.h"

/*
 * initializeStringQueue method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method initializes and allocates memory for an queue of strings with
 * 			a specified size
 * Input Parameters:
 * 		size - the length of string array to initialize
 * Output: The array that was created
 */
StringQueue* initializeStringQueue(int size) {
    StringQueue* s = (StringQueue*)malloc(sizeof(StringQueue));
    s->size = size;
    s->start = 0;
    s->end = -1;
    s->count = 0;
    s->history = malloc(sizeof(s->history[0]) * size);
    return s;
}

/*
 * freeStringQueueData method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method resets and frees memory that was allocated previously
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: None
 */
void freeStringQueueData(StringQueue* qHist) {

    free(qHist->history);
    qHist->count = 0;
    qHist->start = 0;
    qHist->end = -1;
}

/*
 * topStringQueue method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method returns the starting element in the previous command queue
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: A string that contains the first element
 */
char* topStringQueue(StringQueue* qHist) {
    return qHist->history[qHist->start];
}

/*
 * dequeueStringQueue method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method removes the starting element from the command queue
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: The new string, otherwise NULL
 */
char* dequeueString(StringQueue* qHist) {

    if (qHist->count > 0) {
        char* msg = qHist->history[qHist->start];
        qHist->start = (qHist->start + 1) % qHist->size;
        qHist->count--;
        return msg;
    } else {
        return NULL;
    }
}

/*
 * enqueueStringQueue method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method adds an additional string that get enqueued
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 *		msg - the string command in which to add
 * Output: None
 */
void enqueueString(StringQueue* qHist, char* msg) {

    qHist->end = (qHist->end + 1) % qHist->size;
    
    if (qHist->end == qHist->start && qHist->count >= qHist->size) {
        qHist->start = (qHist->end+1)%qHist->size;
    }
    
    if (qHist->count < 10) {
        qHist->count++;
    }
    
    strcpy(qHist->history[qHist->end], msg);
}

/*
 * stringQueueCount method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method returns the number of commands to be executed
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 * Output: The number of commands in integer format
 */
int stringQueueCount(StringQueue* qHist) {
    return qHist->count;
}

/*
 * printStringQueue method
 * Author: Eric Bachmeier
 * Created: January 22, 2016
 * Purpose: This method prints the entire list of commands to the screen for the user
 * Input Parameters:
 * 		qHist - the array of previously executed commands
 *		n - the number of history elements to show
 * Output: None
 */
void printStringQueue(StringQueue* qHist, int n) {

    int j = 1;
    
    if (n < qHist->count) {
        for (int i = 0; i < n; i++) {
            printf("[%d]: %s", qHist->count-n+j++, qHist->history[(qHist->end-n+1+i)%qHist->size]);
        }
    } else {
        for (int i = 0; i < qHist->count; i++) {
            printf("[%d]: %s", j++, qHist->history[(qHist->start+i)%qHist->size]);
        }
    }
}