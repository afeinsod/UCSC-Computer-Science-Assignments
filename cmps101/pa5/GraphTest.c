//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 5, CMPS 101
// GraphTest.c
// Test file for GRAPH ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   	Graph G;
	G = newGraph(4);
	printGraph(stdout, G);
	printf("Order: %d\n", getOrder(G));
	printf("Size: %d\n", getSize(G));
	//should print:
	//1: 
	//2: 
	//3: 
	//4: 
	//Order: 4
	//Size: 0

	addArc(G,1,2);
	addArc(G,1,3);
	addArc(G,2,4);
	//should print:
	//1: 2 3
	//2: 4
	//3: 
	//4: 
	printGraph(stdout, G);
	//should print: Order: 4
	printf("Order: %d\n", getOrder(G));
	//should print: Size: 3
	printf("Size: %d\n", getSize(G));
	
	List L;
	L=newList();
	for (int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	printf("Beginning list: ");
	printList(stdout, L);
	printf("\n");
	//Should print 1 2 3 4 

	printf("Calling DFS on G \n");
	DFS(G, L);
	printf("Parent of 2: %d\n", getParent(G, 2));
	//Should print: 1
	printf("Parent of 3: %d\n", getParent(G, 3));
	//Should print: 1
	printf("Parent of 4: %d\n", getParent(G, 4));
	//Should print: 2
	printf("Parent of 1: %d\n", getParent(G, 1));
	//Should print: 0
	printf("Discover time of 1: %d, Finish time of 1: %d\n", getDiscover(G, 1), getFinish(G, 1));
	//Should print: 1, 8
	printf("Discover time of 2: %d, Finish time of 2: %d\n", getDiscover(G, 2), getFinish(G, 2));
	//Should print: 2, 5
	printf("Discover time of 3: %d, Finish time of 3: %d\n", getDiscover(G, 3), getFinish(G, 3));
	//Should print: 6, 7
	printf("Discover time of 4: %d, Finish time of 4: %d\n", getDiscover(G, 4), getFinish(G, 4));
	//Should print: 3, 4

	printList(stdout, L);
	printf("\n");
	//Should print 1 3 2 4 

	Graph T;
	T=transpose(G);
	printf("Transpose Order: %d\n", getOrder(T));
	printf("Transpose of G: \n");
	printGraph(stdout, T);
    
	printf("Calling DFS on T with L in above order\n");
	DFS(T, L);


	printf("Parent of 2: %d\n", getParent(T, 2));
	//Should print: 0
	printf("Parent of 3: %d\n", getParent(T, 3));
	//Should print: 0
	printf("Parent of 4: %d\n", getParent(T, 4));
	//Should print: 0
	printf("Parent of 1: %d\n", getParent(T, 1));
	//Should print: 0
	printf("Discover time of 1: %d, Finish time of 1: %d\n", getDiscover(T, 1), getFinish(T, 1));
	//Should print: 1, 2
	printf("Discover time of 2: %d, Finish time of 2: %d\n", getDiscover(T, 2), getFinish(T, 2));
	//Should print: 5, 6
	printf("Discover time of 3: %d, Finish time of 3: %d\n", getDiscover(T, 3), getFinish(T, 3));
	//Should print: 3, 4
	printf("Discover time of 4: %d, Finish time of 4: %d\n", getDiscover(T, 4), getFinish(T, 4));
	//Should print: 7, 8

	printList(stdout, L);
	printf("\n");
	//Should print 4 2 3 1

	printf("Order: %d\n", getOrder(G));
	//Should print: Order: 4
	printf("Size: %d\n", getSize(G));
	//Should print: Size: 0

	for (int i =1; i<= getgcc(T); i++) {
		printf("Component %d:", i);
		moveTo(L, 0);
		while(getIndex(L) > -1){
			if (getcc(T, getElement(L)) == i){
			  printf(" %d", getElement(L));
			}
			moveNext(L);
		}
		printf("\n");
	}
	freeList(&L);
	freeGraph(&T);
	freeGraph(&G);
	return(0);
}
