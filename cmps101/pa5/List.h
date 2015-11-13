//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 5, CMPS 101
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------


// length()
// Returns the length of L.
int length(List L);

// getIndex()
// returns the current index of L
int getIndex(List L);

// front()
// Returns the value at the front of L.
// Pre: length(L) != 0
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: length(L) != 0
int back(List L);

// getElement()
// Pre: length(L) != 0, index ! = -1
// returns the current element of L.
int getElement(List L);

// equals()
// Returns true (1) if A is equal to B, otherwise returns false (0)
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

//clear()
// Clears L so that it is an empty list.
void clear(List L);

//moveTo()
//Moves the cursor to index i in list L.
void moveTo(List L, int i);

//movePrev()
//Moves the cursor from its current index to the previous index.
void movePrev(List L);

//moveNext()
//Moves the cursor from its current index to the previous index.
void moveNext(List L);

//prepend()
//Inserts data at the beginning of L.
void prepend(List L, int data);

//append()
//Inserts data at the end of L.
void append(List L, int data);

//insertBefore()
//Inserts data before the current position in L.
//Pre: length(L)>0, getIndex(L)>=0
void insertBefore(List L, int data);

//insertAfter()
//inserts data after the current position in L.
//Pre: length(L)>0, getIndex(L)>=0
void insertAfter(List L, int data);

//deleteFront()
//Deletes the front element in L.
//Pre: length(L)>0
void deleteFront(List L);

//deleteBack()
//Deletes the back element in L.
//Pre: length(L)>0
void deleteBack(List L);

//delete()
//Deletes the current element of L.
//Pre: length(L)>0, getIndex(L)>=0
void delete(List L);


// Other Operations ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to out.
void printList(FILE* out, List L);

//copyList()
//Returns a list which is a copy of List L.
List copyList(List L);

//concatList()
//Returns a list which consists of all the elements in A 
// followed by all the elements in B.
List concatList(List A, List B);

#endif
