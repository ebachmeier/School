/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 4
 * CS3305 Operating Systems
 * Western University
 * Professor Hanan Lutfiyya
 * March 29, 2016
 *
 * deq.h is the implementation for a double-ended queue. This queue allows pushing 
 * and popping from both ends of the queue.
 */

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    int data;
} Node;

typedef struct DEQ {
    struct Node* head;
    struct Node* tail;
    int size;
} DEQ;

/*
 * makeNode method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method creates a node with a value.
 * Input Parameters: 
 *		- value: the integer value for the node
 * Output: A Node struct with pointers to next and previous Nodes.
 */
Node* makeNode(int val) {

	// allocate memory for the Node
    Node* n = (Node*)malloc(sizeof(Node));
    
    // initialize values for the Node
    n->data = val;
    n->next = n->prev = NULL;
    
    return n;
}

/*
 * getDEQ method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method initializes a double-ended queue with 0 items.
 * Input Parameters: None
 * Output: A DEQ struct initialized to 0.
 */
DEQ* getDEQ() {

	// allocate memory for a DEQ struct
    DEQ* d = (DEQ*)malloc(sizeof(DEQ));
    
    // initialize its values to 0
    d->size = 0;
    d->head = d->tail = NULL;
    
    return d;
}

/*
 * pushR method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method pushes a new item onto the right of the queue.
 * Input Parameters: 
 *		- d: DEQ struct
 *		- item: new item to be added onto the right of the queue
 * Output: A boolean return value for the operation.
 */
bool pushR(DEQ* d, int item) {

    if (d == NULL) return false;

    Node* n = makeNode(item);

	// if the queue is empty
    if (d->head == NULL) {
    
    	// make the head and tail nodes equal
        d->head = d->tail = n;
        
    // otherwise, append the new node
    } else {
    
        d->head->prev = n;
        n->next = d->head;
    }
    
    d->head = n;
    d->size++;
    
    return true;
}

/*
 * popR method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method pops an item off of the right of the queue.
 * Input Parameters: 
 *		- d: DEQ struct
 * Output: The value of the item popped off.
 */
int popR(DEQ* d) {

    if (d == NULL) {
        exit(1);
    }

    Node* n = d->head;
    int val = n->data;

	// if there is only one node
    if (n->next == NULL) {
        d->head = d->tail = NULL;
        
    } else {
        d->head = d->head->next;
        d->head->prev = NULL;
    }

    d->size--;
    free(n);

    return val;
}

/*
 * pushL method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method pushes a new item onto the left of the queue.
 * Input Parameters: 
 *		- d: DEQ struct
 *		- item: new item to be added onto the left of the queue
 * Output: A boolean return value for the operation.
 */
bool pushL(DEQ* d, int item) {

    if (d == NULL) return false;

    Node* n = makeNode(item);

	// if the queue is empty
    if (d->tail == NULL) {
    
    	// make the head and tail nodes equal
        d->head = d->tail = n;
        
    // otherwise, append the new node
    } else {
    
        d->tail->next = n;
        n->prev = d->tail;
    }
    
    d->tail = n;
    d->size++;
    
    return true;
}

/*
 * popL method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method pops an item off of the left of the queue.
 * Input Parameters: 
 *		- d: DEQ struct
 * Output: The value of the item popped off.
 */
int popL(DEQ* d) {

    if (d == NULL) {
        exit(1);
    }

    Node* n = d->tail;
    int val = n->data;
	
	// if the queue is empty
    if (n->prev == NULL) {
        d->head = d->tail = NULL;
        
    } else {
        d->tail = d->tail->prev;
        d->tail->next = NULL;
    }

    d->size--;
    free(n);

    return val;
}

/*
 * removeNode method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method removes a given item from the queue.
 * Input Parameters: 
 *		- d: DEQ struct
 *		- item: the item to remove from the queue
 * Output: A boolean return value for the operation.
 */
bool removeNode(DEQ* d, int item) {

	// get pointers for the head and tail of the queue
    Node* h = d->head;
    Node* t = d->tail;
    
    // iterate the queue from top to bottom AND bottom to top at the same time
    while (true) {
    
    	// right to left
        if (h->data == item) {
        
            if (h->prev == NULL) {
                popR(d);
                
            } else {
                Node* n = h;
                n->prev->next = h->next;
                n->next->prev = h->prev;
            }
            
            return true;
            
        // left to right
        } else if (t->data == item) {
        
            if (t->next == NULL) {
                popL(d);
            } else {
            
                Node* n = t;
                n->prev->next = t->next;
                n->next->prev = t->prev;
            }
            
            return true;
        }

        h = h->next;

        // return if at the end they are pointing to the same value in the middle of the queue
        if (h == t) return false;

        t = t->prev;

       	// this is to handle if the end of the queue is reached first
        if (h == NULL || t == NULL) return false;
    }

    return false;
}

/*
 * freeDEQ method
 * Author: Eric Bachmeier
 * Created: March 29, 2016
 * Purpose: This method frees all allocated memory for the double-ended queue. 
 * Input Parameters: 
 *		- d: DEQ struct
 * Output: None.
 */
void freeDEQ(DEQ* d) {

    if (d == NULL) return;
    if (d->head == NULL) return;
    
    while (d->head->next != NULL) {
        Node* n = d->head;
        d->head = d->head->next;
        free(n);
    }
    
    free(d);
}