//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B/M
//queue.h
//Header file for queue linked list for lab 6

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

// NAME
//    queue
//
// DESCRIPTION
//    A simple queue that makes a first in, first out linked list
//    from user input.


struct queue;
    // Incomplete type defined in implementation file.

typedef struct queue queue;
    // Incomplete type defined in implementation file.

typedef char *queue_item_t;
    // Incomplete type defined in implementation file.


/* Function declarations */

queue *queue_new(void);
    // Constructor: create a new `queue' with no elements.
    // Postcond:    new queue is returned

void queue_free(queue*);
    // Destructor: destroys an allocated queue
    // Precond:   queue created by queue_new.
    // Postcond:   this pointer is dangling.

void queue_insert(queue*, queue_item_t);
    // Mutator:    Inserts an item into the back of the queue
    // Precond:    valid pointer to a queue.
    // Postcond:   item is added into given queue

queue_item_t queue_remove(queue*);
    // Mutator:    Removes an item from the front of the queue.
    // Precond:    valid pointer to a nonempty queue.
    // Postcond:   front item of queue is removed and returned


bool queue_isempty(queue*);
    // Accessor:   finds out if queue is empty or not.
    // Precond:    valid pointer to a queue.
    // Postcond:   returns true if there are no items in the 
    //             queue, false otherwise.


#endif
