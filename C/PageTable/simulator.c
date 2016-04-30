/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 4
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * March 28, 2016
 *
 * To compile and run:
 * 		$ make
 *		$ ./simulator 4 trace LRU
 *                    	- number of frames
 *						- file containing the memory trace
 *						- LRU or LFU
 *
 * simulator.c simulates Least Frequently Used and Least Recently Used virtual memory
 * replacement algorithms utilizing translation lookaside buffer optimization.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "deq.h"

// definitions for the two virtual memory replacement algorithms
#define LRU 0
#define LFU 1

// size of the table for the translation lookaside buffer
#define TLB_SIZE 7

#define LINE_SIZE 82

typedef struct PageInfo {
    int frameNumber;
    // boolean where valid = 1
    bool valid;
    int numberReferences;
} PageInfoEntry;

typedef struct TLBInfo {
    int pageNumber;
    int frameNumber;
    int hitCount;
} TLBInfoEntry;

/*
 * parseFile method
 * Author: Eric Bachmeier
 * Created: March 28, 2016
 * Purpose: This method parses the passed file and adds the page table trace to the queue.
 * Input Parameters: 
 *		- filename: The filename passed by the user
 * Output: A DEQ struct populated from the left from the page table.
 */
DEQ* parseFile(char* filename) {

    FILE* f = fopen(filename, "r");
    
    if (f == NULL) {
        printf("\tError: Cannot open memory trace file\n");
        exit(1);
    }

    DEQ* d = getDEQ();

    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, f) != NULL) {
    	// push the memory trace line to the left of the queue
        pushL(d, atoi(line));
    }

    return d;
}

/*
 * main method
 * Author: Eric Bachmeier
 * Created: March 28, 2016
 * Purpose: This is the main method for the simulator.
 * Input Parameters: Command-line arguments for the number of frames, the
 * file for memory trace, and the replacement policy to use.
 * Output: Integer exit code status.
 */
int main(int argc, char** argv) {
    if (argc != 4) {
        printf("\tUsage:   ./simulator <number of frames> <trace file> <LRU or LFU>\n\tExample: ./simulator 4 trace LRU\n");
        exit(1);
    }

    int nFrames = atoi(argv[1]);
    char* filename = argv[2];
    char* policy = argv[3];

    const unsigned int pageTableSize = 1024;
    
    bool m = 0;
    int numberFaults = 0;
    int numberFramesUsed = 0;

    int TLBmisses = 0;
    int TLBtotal = 0;

    if (strcmp(policy, "LRU") == 0 || strcmp(policy, "LFU") == 0) {
        m = strcmp(policy, "LRU") == 0 ? LRU : LFU;
        
    } else {
        printf("\tError: Argument 3 must be policy LRU or LFU\n");
        exit(1);
    }

	// read in the page table from the passed file
    DEQ* traces = parseFile(filename);
    
    // initialize a queue to store the most recent on right and least recently used on 
    // the left
    DEQ* leastRecent = getDEQ();

    // initialize the translation lookaside buffer
    TLBInfoEntry* buffer = (TLBInfoEntry*) malloc(sizeof(TLBInfoEntry) * TLB_SIZE);
    
    for (int i = 0; i < TLB_SIZE; i++) {
        buffer[i].frameNumber = -1;
        buffer[i].hitCount = 0;
        buffer[i].pageNumber = -1;
    }

    // initialize the page table
    PageInfoEntry* pageTable = (PageInfoEntry*) malloc(sizeof(PageInfoEntry) * pageTableSize);
    
    for (int i = 0; i < pageTableSize; i++) {
        pageTable[i].frameNumber = 0;
        pageTable[i].numberReferences = 0;
        pageTable[i].valid = false;
    }

	// while traces still exist that we read in, get the next trace in order
    while (traces->size > 0) {
    
        int pageIndex = popR(traces);

		// reference the page and add to the count for LFU
        pageTable[pageIndex].numberReferences++;

		// remove the page if it is valid
        if (pageTable[pageIndex].valid) {

            // simulate parallel TLB lookup of page reference
            // must use serial lookup for simulation
            
            // boolean for if the page is found in the TLB
            bool found = false;
            
            for (int i = 0; i < TLB_SIZE; i++) {
            
                if (buffer[i].pageNumber == pageIndex) {
                    buffer[i].hitCount++;
                    found = true;
                }
            }
            
            // if the page is not found in the TLB
            if (!found) {
            
            	// count the miss
                TLBmisses++;
                
                // add the missed item to the buffer
                if (TLBtotal < TLB_SIZE) {
                    buffer[TLBtotal].pageNumber = pageIndex;
                    buffer[TLBtotal].frameNumber = pageTable[pageIndex].frameNumber;
                    
                } else {
                    
                    // find and replace the least recently used page
                    int minHitCount = INT_MAX;	// INT_MAX defined in limits.h
                    int minHitIndex = 0;
                    
                    for (int i = 0; i < TLB_SIZE; i++) {
                    
                        if (buffer[i].hitCount < minHitCount) {
                            minHitCount = buffer[i].hitCount;
                            minHitIndex = i;
                        }
                    }
                    
                    buffer[minHitIndex].pageNumber = pageIndex;
                    buffer[minHitIndex].frameNumber = pageTable[pageIndex].frameNumber;
                }

                // use the page table if the given page reference number was not found in 
                // TLB
                if (m == LRU) {
                
                	// push the page back onto the left of the queue
                    removeNode(leastRecent, pageIndex);
                    pushR(leastRecent, pageIndex);
                }
            }
            
        } else {
        
        	// increase the number of faults if the item was not valid
            numberFaults++;

            int frameUnique = 0;
            
            if (numberFramesUsed < nFrames) {
            
                frameUnique = numberFramesUsed++;
                
                // push to the left of the least recently used queue
                pushL(leastRecent, frameUnique);
                
            } else {
            
                switch (m) {
                	
                	// get the least recently used item off the stack
                    case LRU: {
                    
                    	// remove the rightmost item in the least recently used stack
                        int topframeUnique = popR(leastRecent);
                        
                        // get the frame number
                        frameUnique = pageTable[topframeUnique].frameNumber;
                        
                        // make sure the old frame is now invalid
                        pageTable[topframeUnique].valid = false;
                        
                        // push the new frame on the left
                        pushL(leastRecent, topframeUnique);
                        
                        break;
                    }
                    
                    // get the item which has been least used
                    case LFU: {
                    
                        // we want the item with the least number of references
                        int minIndex = 0;
                        int minReferences = INT_MAX;
                        
                        for (int i = 0; i < pageTableSize; i++) {
                        
                            if (pageTable[i].valid) {
                            
                                if (pageTable[i].numberReferences == 0) {
                                    minIndex = i;
                                    break;
                                }
                                
                                // if none have 0 references, keep searching for the min
                                if (pageTable[i].numberReferences < minReferences) {
                                    minReferences = pageTable[i].numberReferences;
                                    minIndex = i;
                                }
                            }
                        }
                        
                        // make the used page invalid
                        pageTable[minIndex].valid = false;
                        
                        // update the new frame number
                        frameUnique = pageTable[minIndex].frameNumber;
                        
                        break;
                    }
                    	
                    // default case for switch statement
                    default: break;
                }
            }
            
            // update the frame and reset the counters
            pageTable[pageIndex].frameNumber = frameUnique;
            pageTable[pageIndex].numberReferences = 0;
            pageTable[pageIndex].valid = true;
        }
    }
	
	// free any allocated memory for the queues and page table
    freeDEQ(leastRecent);
    freeDEQ(traces);
    free(pageTable);

    printf("\tPage faults : %d\n\tTLB misses  : %d\n", numberFaults, TLBmisses);
    
    return 0;
}
