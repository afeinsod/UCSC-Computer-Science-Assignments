//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 5, CMPS 101
// Graph.c
// Implementation file for GRAPH ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

/***Structs***/
// private GraphObj type
typedef struct GraphObj{
   int order;
   List* vneighbor;
   char* vcolor;
   int* vparent;
   int* vdiscover;
   int* vfinish;
   int* vcc;
   int size;
   int numcc;
} GraphObj;


/*** Constructors-Destructors***/

//returns a newly created Graph Obj representing a graph having n vertices and no edges.
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->vneighbor = calloc(n+1, sizeof(List));
	for (int i = 0; i <= n; i++) {
		G->vneighbor[i] = newList();
		}
	G->vcolor = calloc(n+1, sizeof(char));
	for (int i = 0; i <= n; i++) {
		G->vcolor[i] = 'w';
		}
	G->vparent = calloc(n+1, sizeof(int));
	for (int i = 0; i <= n; i++) {
		G->vparent[i] = NIL;
		}
	G->vdiscover = calloc(n+1, sizeof(int));
	for (int i = 0; i <= n; i++) {
		G->vdiscover[i] = INF;
		}
	G->vfinish = calloc(n+1, sizeof(int));
	for (int i = 0; i <= n; i++) {
		G->vfinish[i] = INF;
		}
	G->vcc=calloc(n+1,sizeof(int));
	for (int i = 0; i <=n; i++) {
		G->vcc[i]=0;
		}
	G->order = n;
	G->size = 0;
	G->numcc=0;
	return(G);
}

//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
	if ((pG != NULL) && (*pG != NULL)) {
	  	for (int i = 0; i <= (*pG)->order; i++) {
			freeList(&((*pG)->vneighbor[i]));
			}
		free((*pG)->vneighbor);
		free((*pG)->vcolor);
		free((*pG)->vparent);
		free((*pG)->vdiscover);
		free((*pG)->vfinish);
	       	free((*pG)->vcc);
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions***/

//returns the order of graph G
int getOrder(Graph G) {
	if( G == NULL ){
      		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      		exit(1);
	}
	return(G->order);
}

//returns the size of graph G
int getSize(Graph G) {
	if( G == NULL ){
      		printf("Graph Error: calling getSize() on NULL Graph reference\n");
      		exit(1);
	}
	return(G->size);
}

//will return the parent of vertex u in the Depth-First tree created by FFS(), or NIL
//if either u has no parent or DFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getParent(Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getParent() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getParent() on invalid vertex value\n");
      		exit(1);
	}
	return(G->vparent[u]);
}

//will return the discover time of vertex u by DFS(), or NIL
//if DFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getDiscover(Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getDiscover() on invalid vertex value\n");
      		exit(1);
	}
	return(G->vdiscover[u]);
}

//will return the finish time of vertex u by DFS(), or NIL
//if DFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getFinish(Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getFinish() on invalid vertex value\n");
      		exit(1);
	}
	return(G->vfinish[u]);
}	

//will return the number of strongly connected components in G
int getgcc(Graph G) {
	if( G == NULL ){
      		printf("Graph Error: calling getgcc() on NULL Graph reference\n");
      		exit(1);
	}
	return(G->numcc);
}

//returns number of connected component with u as an element
//pre: u between 1 and getOrder(G)
int getcc(Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getcc() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getcc() on invalid vertex value\n");
      		exit(1);
	}
	return(G->vcc[u]);
}

/*** Manipulation procedures***/	

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of
//v, and v to the adjacency List of u (maintaining both lists in sorted order).
//Pre: u and v between 1 and getOrder(G)
void addEdge(Graph G, int u, int v) {
	if( G == NULL ){
      		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G)) || (1>v) || (v > getOrder(G))) {
      		printf("Graph Error: calling addEdge() on invalid vertex value\n");
      		exit(1);
	}
	//insert u into v:
	//goes to beginning of v's neighbor list
	moveTo(G->vneighbor[v],0);
	//moves to correct stop in the list
	while((getIndex(G->vneighbor[v]) > -1) && (getElement(G->vneighbor[v]) < u)) {
		moveNext(G->vneighbor[v]);
	}
	//checks if we are off the end of the list
	if (getIndex(G->vneighbor[v]) == -1) {
		append(G->vneighbor[v], u);
		G->size++;
	}
	//if not off end of list, insert before current position
	else {
		insertBefore(G->vneighbor[v], u);
		G->size++;
	}
	//insert v into u:
	//goes to beginning of u's neighbor list
	moveTo(G->vneighbor[u],0);
	//moves to correct stop in the list
	while((getIndex(G->vneighbor[u]) > -1) && (getElement(G->vneighbor[u]) < v)) {
		moveNext(G->vneighbor[u]);
	}
	//checks if we are off the end of the list
	if (getIndex(G->vneighbor[u]) == -1) {
		append(G->vneighbor[u], v);
	}
	//if not off end of list, insert before current position
	else {
		insertBefore(G->vneighbor[u], v);
	}
}

//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of
//u (but not u to the adjacency List of v). 
//Pre: u and v between 1 and getOrder(G)
void addArc(Graph G, int u, int v) {
	if( G == NULL ) {
      		printf("Graph Error: calling addArc() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G)) || (1>v) || (v > getOrder(G))) {
      		printf("Graph Error: calling addArc() on invalid vertex value\n");
      		exit(1);
	}
	//insert v into u:
	//goes to beginning of u's neighbor list
	moveTo(G->vneighbor[u],0);
	//moves to correct stop in the list
	while((getIndex(G->vneighbor[u]) > -1) && (getElement(G->vneighbor[u]) < v)) {
		moveNext(G->vneighbor[u]);
	}
	//checks if we are off the end of the list
	if (getIndex(G->vneighbor[u]) == -1) {
		append(G->vneighbor[u], v);
		G->size++;
	}
	//if not off end of list, insert before current position
	else {
		insertBefore(G->vneighbor[u], v);
		G->size++;
	}
}

//helper recursive function for DFS
int visit(Graph G, List S, int u, int* time, int k){
	*time = *time + 1;
	G->vdiscover[u] = *time;
	G->vcolor[u]= 'g';
	G->vcc[u]=k;
	moveTo(G->vneighbor[u],0);
	while (getIndex(G->vneighbor[u]) > -1) {
		int v;
		v = getElement(G->vneighbor[u]);
		if (G->vcolor[v] == 'w') {
			G->vparent[v] = u;
			visit(G, S, v, time, k);
		}
		moveNext(G->vneighbor[u]);
	}
	G->vcolor[u]='b';
	*time = *time + 1;
	G->vfinish[u] = *time;
	if (getIndex(S) > -1) {
		insertAfter(S, u);
	}
	else {
		prepend(S, u);
	}
	return *time;
}

//runs the DFS algorithm on the Graph G, using the List S to order the vertices
//and store the stack of finished vertices.
//Pre: Length of S = order of G, S has all the correct numbers in it(does not check this)
void DFS(Graph G, List S){
	if( G == NULL ) {
      		printf("Graph Error: calling DFS() on NULL Graph reference\n");
      		exit(1);
	}
	if( S == NULL ) {
      		printf("Graph Error: calling DFS() on NULL List reference\n");
      		exit(1);
	}
	if( length(S) != getOrder(G) ) {
      		printf("Graph Error: calling DFS() on wrong length list\n");
      		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++) {
		G->vcolor[i]='w';
		G->vparent[i]=NIL;
	}
	int time;
	time =0;
	int k;
	k=0;

	moveTo(S, getOrder(G)-1);
	for(int i = 1; i <= getOrder(G); i++) {
		int u;
		u = front(S);
		deleteFront(S);
		if (G->vcolor[u] == 'w'){
			k=k+1;
			time = visit(G, S, u, &time, k);
			G->numcc=k;
		}
	}
}



/*** Other operations***/

//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
	if( G == NULL ) {
      		printf("Graph Error: calling transpose() on NULL Graph reference\n");
      		exit(1);
	}
	Graph H;
	H=newGraph(getOrder(G));
	for(int i=1; i <= getOrder(G); i++) {
		if(length(G->vneighbor[i]) != 0) {
			moveTo(G->vneighbor[i], 0);
			while(getIndex(G->vneighbor[i]) > -1) {
				addArc(H, getElement(G->vneighbor[i]),i);
				moveNext(G->vneighbor[i]);
			}
		}
	}
	return H;
}

//Returns a reference to a new graph object that is a copy of G
Graph copyGraph(Graph G){
	if( G == NULL ) {
      		printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
      		exit(1);
	}
	Graph H;
	H=newGraph(getOrder(G));
	for(int i; i <= getOrder(G); i++) {
		H->vneighbor[i]=copyList(G->vneighbor[i]);
   		H->vcolor[i]=G->vcolor[i];
   		H->vparent[i]=G->vparent[i];
   		H->vdiscover[i]=G->vdiscover[i];
   		H->vfinish[i]=G->vfinish[i];
   	}
	H->size = getSize(G);
	return H;
}

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	if( G == NULL ) {
      		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->vneighbor[i]);
		fprintf(out, "\n");
	}
}
