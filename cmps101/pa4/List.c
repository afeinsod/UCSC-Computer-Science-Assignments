//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment #4, Computer Science 101
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* previous;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int cursorIndex;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while (length(*pL) > 0) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L) {
	if( L==NULL ){
      		printf("List Error: calling length() on NULL List reference\n");
      		exit(1);
	}
	return(L->length);
}

// getIndex()
// returns the current index of L
int getIndex(List L) {
	if( L==NULL ){
      		printf("List Error: calling getIndex() on NULL List reference\n");
      		exit(1);
	}
	return(L->cursorIndex);
}

// front()
// Returns the value at the front of L.
// Pre: length(L) != 0
int front(List L) {
	if( L==NULL ){
      		printf("List Error: calling front() on NULL List reference\n");
      		exit(1);
	}
	if (L->length == 0) {
		printf("List Error: calling front() on empty List\n");
		exit(1);
	}
	return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: length(L) != 0
int back(List L) {
	if( L==NULL ){
      		printf("List Error: calling back() on NULL List reference\n");
      		exit(1);
	}
	if (L->length == 0) {
		printf("List Error: calling back() on empty List\n");
		exit(1);
	}
	return(L->back->data);
}

// getElement()
// Pre: length(L) != 0, index ! = -1
// returns the current element of L.
int getElement(List L) {
	if( L==NULL ){
      		printf("List Error: calling getElement() on NULL List reference\n");
      		exit(1);
	}
	if (L->length == 0) {
		printf("List Error: calling getElement() on empty List\n");
		exit(1);
	}
	if (L->cursorIndex == -1) {
		printf("List Error: calling getElement() on List with undefined cursor\n");
		exit(1);
	}
	return(L->cursor->data);
}

// equals()
// Returns true (1) if A is equal to B, otherwise returns false (0)
int equals(List A, List B){
   int flag = 1;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}

// Manipulation procedures ----------------------------------------------------

//clear()
// Clears L so that it is an empty list.
void clear(List L) {
	if( L==NULL ){
      		printf("List Error: calling clear() on NULL List reference\n");
      		exit(1);
	}
	if(length(L) != 0) {
	  Node N = L->front;
	  while (N->next != NULL) {
		N = N->next;
		freeNode(&N->previous);
	  }
	  freeNode(&N);
	  L->front = L->back = L->cursor = NULL;
	  L->length = 0;
	  L->cursorIndex = -1;
	}
}

//moveTo()
//Moves the cursor to index i in list L.
void moveTo(List L, int i) {
	if( L==NULL ){
      		printf("List Error: calling moveTo() on NULL List reference\n");
      		exit(1);
	}
	if ((0<=i) && (i<=(L->length-1))) {
			L->cursorIndex = i;
			L->cursor = L->front;
			if (i != 0) {
				for (int j = 0; j<i; j++) {
					L->cursor = L->cursor->next;
				}
			}
		}
		else {
			L->cursorIndex = -1;
			L->cursor = NULL;
		}
	}

//movePrev()
//Moves the cursor from its current index to the previous index.
void movePrev(List L) {
	if( L==NULL ){
      		printf("List Error: calling movePrev() on NULL List reference\n");
      		exit(1);
	}
	if ((0<L->cursorIndex) && (L->cursorIndex <= (L->length-1))) {
			L->cursor = L->cursor->previous;
			L->cursorIndex --;
		}
		else if (L->cursorIndex == 0) {
			L->cursor = NULL;
			L->cursorIndex = -1;
		}
		else {}
	}

//moveNext()
//Moves the cursor from its current index to the previous index.
void moveNext(List L) {
	if( L==NULL ){
      		printf("List Error: calling moveNext() on NULL List reference\n");
      		exit(1);
	}
	if ((0<=L->cursorIndex) && (L->cursorIndex < (L->length-1))) {
			L->cursor = L->cursor->next;
			L->cursorIndex ++;
		}
		else if (L->cursorIndex == (L->length-1)) {
			L->cursor = NULL;
			L->cursorIndex = -1;
		}
		else {}
	}

//prepend()
//Inserts data at the beginning of L.
void prepend(List L, int data) {
	if( L==NULL ){
      		printf("List Error: calling prepend() on NULL List reference\n");
      		exit(1);
	}
	Node n = newNode(data);
	if (L->length == 0) {
		L->front=L->back=n;
                       L->length++;
	}
	else {
		L->front->previous = n;
		n->next = L->front;
		L->front = n;
		L->length ++;
	}
}

//append()
//Inserts data at the end of L.
void append(List L, int data) {
	if( L==NULL ){
      		printf("List Error: calling append() on NULL List reference\n");
      		exit(1);
	}
	Node n = newNode(data);
	if (L->length == 0) {
		L->front=L->back=n;
                L->length++;
	}
	else {
		L->back->next = n;
		n->previous = L->back;
		L->back = n;
		L->length ++;
	}
}

//insertBefore()
//Inserts data before the current position in L.
//Pre: length(L)>0, getIndex(L)>=0
void insertBefore(List L, int data) {
	if( L==NULL ){
      		printf("List Error: calling insertBefore() on NULL List reference\n");
      		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: calling insertBefore() on empty List\n");
      		exit(1);
	}
	else if (getIndex(L) <0) {
		printf("List Error: calling insertBefore() with null index\n");
      		exit(1);
	}
	else {
		Node n = newNode(data);
		if (L->cursor == L->front) {
			L->front = n;
			n->next = L->cursor;
			L->cursor->previous = n;
			L->length ++;
			L->cursorIndex ++;
		}
		else {
			L->cursor->previous->next = n;
			n->previous = L->cursor->previous;
			n->next = L->cursor;
			L->cursor->previous = n;
			L->length ++;
			L->cursorIndex ++;
		}
	}
}


//insertAfter()
//inserts data after the current position in L.
//Pre: length(L)>0, getIndex(L)>=0
void insertAfter(List L, int data) {
	if( L==NULL ){
      		printf("List Error: calling insertAfter() on NULL List reference\n");
      		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: calling insertAfter() on empty List\n");
      		exit(1);
	}
	else if (getIndex(L) <0) {
		printf("List Error: calling insertAfter() with null index\n");
      		exit(1);
	}
	else {
		Node n = newNode(data);
		if (L->cursor == L->back) {
			L->back = n;
			n->previous = L->cursor;
			L->cursor->next = n;
			L->length ++;
		}
		else {
			L->cursor->next->previous = n;
			n->next = L->cursor->next;
			n->previous = L->cursor;
			L->cursor->next = n;
			L->length ++;
		}
	}
}

//deleteFront()
//Deletes the front element in L.
//Pre: length(L)>0
void deleteFront(List L) {
	Node N = NULL;
	if( L==NULL ){
      		printf("List Error: calling deleteFront() on NULL List reference\n");
      		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: calling deleteFront() on empty List\n");
      		exit(1);
	}
	N = L->front;
	if(L->length > 1) {
		L->front = L->front->next;
	}
	else {
		L->front = NULL;
	}
	if (L->cursorIndex == 0) {
		L->cursorIndex = -1;
		L->cursor = NULL;
	}
	L->length --;
	freeNode(&N);
}

//deleteBack()
//Deletes the back element in L.
//Pre: length(L)>0
void deleteBack(List L){
	if( L==NULL ){
      		printf("List Error: calling deleteBack() on NULL List reference\n");
      		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: calling deleteBack() on empty List\n");
      		exit(1);
	}
	else {
		if (L->cursor == L->back) {
			L->cursorIndex = -1;
			L->cursor = NULL;
		}
		L->back = L->back->previous;
		freeNode(&L->back->next);
		L->length --;
	}
}

//delete()
//Deletes the current element of L.
//Pre: length(L)>0, getIndex(L)>=0
void delete(List L) {
	if( L==NULL ){
      		printf("List Error: calling delete() on NULL List reference\n");
      		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: calling delete() on empty List\n");
      		exit(1);
	}
	else if (getIndex(L) <0) {
		printf("List Error: calling delete() with null index\n");
      		exit(1);
	}
	else {
		L->cursor->previous->next = L->cursor->next;
		L->cursor->next->previous = L->cursor->previous;
		L->cursorIndex = -1;
		freeNode(&L->cursor);
		L->cursor = NULL;
		L->length --;
	}
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to out.
void printList(FILE* out, List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
}

//copyList()
//Returns a list which is a copy of List L.
List copyList(List L){
	if( L==NULL ){
      		printf("List Error: calling copyList() on NULL List reference\n");
      		exit(1);
   	}
	List l = newList();
	l->front = L->front;
	Node n = L->front;
	while (n != NULL) {
		append(l, n->data);
		n = n->next;
	}
	l->back = L->back;
	return(l);
}


//concatList()
//Returns a list which consists of all the elements in A 
// followed by all the elements in B.
List concatList(List A, List B){
	if( A == NULL || B == NULL){
      		printf("List Error: calling concatList() on NULL List reference\n");
      		exit(1);
   	}
	List n = newList();
	n->front = A->front;
	n->back = B->back;
	Node a = A->front;
	while (a != NULL) {
		append(n, a->data);
		a = a->next;
	}
	a=B->front;
	while (a != NULL) {
		append(n, a->data);
		a = a->next;
	}
	return n;
}
