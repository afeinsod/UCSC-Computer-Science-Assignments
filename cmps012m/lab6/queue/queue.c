//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B/M
//queue.c
//implementation of linked list queue for lab 6

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node {
   queue_item_t item;
   struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue {
   queue_node *front;
   queue_node *rear;
};

/* Functions */

queue *queue_new(void) {
   queue *this = malloc(sizeof (struct queue));
    assert(this != NULL);
    this->front = NULL;
    this->rear = NULL;
    return this;

}

void queue_free(queue *this) {
   assert(queue_isempty(this));
   free(this);
}

void queue_insert(queue *this, queue_item_t item) {
	if (this != NULL) {
		struct queue_node *newnode = malloc(sizeof (struct queue_node));
   		if (this->front == NULL) {
    			assert(newnode != NULL);
			newnode->item = item;
			this->front = newnode;
			this->rear = newnode;
		}
		else {
			assert(newnode != NULL);
			newnode->item = item;
			this->rear->link = newnode;
			this->rear = newnode;
		}
	}
	return;
}

queue_item_t queue_remove(queue *this) {
   assert(!queue_isempty(this));
   	if (this->front == this->rear) {
		queue_item_t temp = this->front->item;
		struct queue_node *tempnode = this->front;
		this->front = NULL;
		free(this->front);
		this->rear = NULL;
		free(this->rear);
		free(tempnode);
		return temp;
	}
	else {
		queue_item_t temp = this->front->item;
		struct queue_node *tempnode = this->front;
		this->front = this->front->link;
		free(tempnode);
		return temp;
	}
}

bool queue_isempty(queue *this) {
   return this->front == NULL;
}
