//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 4, CMPS 101
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
	


	addEdge(G,1,2);
	addEdge(G,1,3);
	addEdge(G,2,4);
	//should print:
	//1: 2 3
	//2: 1 4
	//3: 1
	//4: 2
	printGraph(stdout, G);
	//should print: Order: 4
	printf("Order: %d\n", getOrder(G));
	//should print: Size: 3
	printf("Size: %d\n", getSize(G));
	

	printf("Calling BFS on 1 \n");
	BFS(G, 1);
	printf("Parent of 2: %d\n", getParent(G, 2));
	//Should print: 1
	printf("Parent of 3: %d\n", getParent(G, 3));
	//Should print: 1
	printf("Parent of 4: %d\n", getParent(G, 4));
	//Should print: 2
	printf("Parent of 1: %d\n", getParent(G, 1));
	//Should print: 0
	printf("Source for G: %d\n", getSource(G));
	//Should print: 1
	printf("Distance from 1 to 1: %d\n", getDist(G, 1));
	//Should print: 0
	printf("Distance from 1 to 2: %d\n", getDist(G, 2));
	//Should print: 1
	printf("Distance from 1 to 3: %d\n", getDist(G, 3));
	//Should print: 1
	printf("Distance from 1 to 4: %d\n", getDist(G, 4));
	//Should print: 2

	List L;
	L = newList();
	getPath(L, G, 4);
	printf("Shortest path from 1 to 4: ");
	printList(stdout, L);
	printf("\n");
	//should print: 1 2 4

	List M;
	M= newList();
	getPath(M, G, 2);
	printf("Shortest path from 1 to 2: ");
	printList(stdout, M);
	printf("\n");
	//should print: 1 2

	List N;
	N = newList();
	getPath(N, G, 3);
	printf("Shortest path from 1 to 3: ");
	printList(stdout, N);
	printf("\n");
	//should print: 1 3
	
	List O;
	O= newList();
	getPath(O, G, 1);
	printf("Shortest path from 1 to 1: ");
	printList(stdout, O);
	printf("\n");
	//should print: 1

	printf("Calling BFS on 4 \n");
	BFS(G, 4);
	printf("Parent of 2: %d\n", getParent(G, 2));
	//Should print: 4
	printf("Parent of 3: %d\n", getParent(G, 3));
	//Should print: 1
	printf("Parent of 4: %d\n", getParent(G, 4));
	//Should print: 0
	printf("Parent of 1: %d\n", getParent(G, 1));
	//Should print: 2
	printf("Source for G: %d\n", getSource(G));
	//Should print: 4
	printf("Distance from 4 to 1: %d\n", getDist(G, 1));
	//Should print: 2
	printf("Distance from 4 to 2: %d\n", getDist(G, 2));
	//Should print: 1
	printf("Distance from 4 to 3: %d\n", getDist(G, 3));
	//Should print: 3
	printf("Distance from 4 to 4: %d\n", getDist(G, 4));
	//Should print: 0

	clear(L);
	getPath(L, G, 4);
	printf("Shortest path from 4 to 4: ");
	printList(stdout, L);
	printf("\n");
	//should print: 4

	clear(M);
	getPath(M, G, 2);
	printf("Shortest path from 4 to 2: ");
	printList(stdout, M);
	printf("\n");
	//should print: 4 2

	clear(N);
	getPath(N, G, 3);
	printf("Shortest path from 4 to 3: ");
	printList(stdout, N);
	printf("\n");
	//should print: 4 2 1 3
	
	clear(O);
	getPath(O, G, 1);
	printf("Shortest path from 4 to 1: ");
	printList(stdout, O);
	printf("\n");
	//should print: 4 2 1

	printf("Calling makeNull on G\n");
	makeNull(G);
	printf("Order: %d\n", getOrder(G));
	//Should print: Order: 4
	printf("Size: %d\n", getSize(G));
	//Should print: Size: 0
	freeList(&L);
	freeList(&M);
	freeList(&N);
	freeList(&O);
	freeGraph(&G);
	return(0);
}
