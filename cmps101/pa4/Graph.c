//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 4, CMPS 101
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
   int* vdistance;
   int size;
   int source;
} GraphObj;


/*** Constructors-Destructors***/

//returns a newly created Graph Obj representing a graph having n vertices and no edges.
Graph newGraph(int n) {
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->vneighbor = calloc(n+1, sizeof(List));
	for (int i = 1; i <= n; i++) {
		G->vneighbor[i] = newList();
		}
	G->vcolor = calloc(n+1, sizeof(char));
	for (int i = 1; i <= n; i++) {
		G->vcolor[i] = 'w';
		}
	G->vparent = calloc(n+1, sizeof(int));
	for (int i = 1; i <= n; i++) {
		G->vparent[i] = NIL;
		}
	G->vdistance = calloc(n+1, sizeof(int));
	for (int i = 1; i <= n; i++) {
		G->vdistance[i] = INF;
		}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return(G);
}

//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
	if ((pG != NULL) && (*pG != NULL)) {
	  	for (int i = 1; i <= (*pG)->order; i++) {
			freeList(&((*pG)->vneighbor[i]));
			}
		free((*pG)->vneighbor);
		free((*pG)->vcolor);
		free((*pG)->vparent);
		free((*pG)->vdistance);
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


//returns the most recently used source vertex of graph G
int getSource(Graph G) {
	if( G == NULL ){
      		printf("Graph Error: calling getSource() on NULL Graph reference\n");
      		exit(1);
	}
	return(G->source);
}

//will return the parent of vertex u in the Breadth-First tree created by BFS(), or NIL
//if either u has no parent or BFS() has not yet been called.
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

//returns the distance from the most recent BFS source to vertex u, or INF if
//either u is not reachable from the source or if BFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getDist(Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getDist() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getDist() on invalid vertex value\n");
      		exit(1);
	}
	return(G->vdistance[u]);
}

//appends to the List L the vertices of a shortest path in G from source to u, or 
//appends to L the value NIL if no such path exists. getPath() has the precondition
//getSource(G)!=NIL, so BFS() must be called before getPath()
//Pre: u between 1 and getOrder(G)
void getPath(List L, Graph G, int u) {
	if( G == NULL ){
      		printf("Graph Error: calling getPath() on NULL Graph reference\n");
      		exit(1);
	}
	if( L == NULL ){
      		printf("Graph Error: calling getPath() on NULL List reference\n");
      		exit(1);
	}
	if((1>u) || (u > getOrder(G))) {
      		printf("Graph Error: calling getPath() on invalid vertex value\n");
      		exit(1);
	}
	if(getSource(G) == NIL) {
		printf("Graph Error: calling getPath() before BFS()\n");
		exit(1);
	}
	//begin actual print path algorithm
	if(G->vdistance[u] == 0) {
		append(L, u);
	}
	else if (G->vparent[u] == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, G->vparent[u]);
		append(L, u);
	}
}
	

/*** Manipulation procedures***/

//deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G) {
	if( G == NULL ){
      		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      		exit(1);
	}
	//clears all the edges in G
	for (int i = 0; i <= getOrder(G); i++) {
		if (G->vneighbor[i] != NULL) {
			clear(G->vneighbor[i] );
		}
	}
	//restores G size to 0
	G->size = 0;
}	

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

//runs the BFS algorithm on the Graph G with source s, setting the color, distance,
//parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
	if( G == NULL ) {
      		printf("Graph Error: calling BFS() on NULL Graph reference\n");
      		exit(1);
	}
	if((1>s) || (s > getOrder(G))) {
      		printf("Graph Error: calling BFS() on invalid vertex value\n");
      		exit(1);
	}
	//start actual BFS algorithm
	for (int i = 1; i <= getOrder(G); i++) {
		G->vcolor[i] = 'w';
		G->vdistance[i] = INF;
		G->vparent[i] = NIL;
	}
	G->source = s;
	G->vcolor[s]= 'g';
	G->vdistance[s] = 0;
	List Q;
	Q = newList();
	append(Q,s);
	while (length(Q) != 0) {
		moveTo(Q,0);
		int u;
		u = getElement(Q);
		deleteFront(Q);
		moveTo(G->vneighbor[u],0);
		while (getIndex(G->vneighbor[u]) != -1) {
			int v = getElement(G->vneighbor[u]);
			if(G->vcolor[v] == 'w') {
				G->vcolor[v] = 'g';
				G->vdistance[v] = G->vdistance[u] + 1;
				G->vparent[v] = u;
				append(Q, v);
			}
			moveNext(G->vneighbor[u]);	
		}
		G->vcolor[u] = 'b';
	}
	freeList(&Q);
}

/*** Other operations***/

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
