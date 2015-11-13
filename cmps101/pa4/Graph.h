//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 4, CMPS 101
// Graph.h
// Header file for GRAPH ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL 0
#define INF -1
#include"List.h"

/*** Exported type***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors***/

//returns a newly created Graph Obj representing a graph having n vertices and no edges.
Graph newGraph(int n);

//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG);

/*** Access functions***/

//returns the order of graph G
int getOrder(Graph G);

//returns the size of graph G
int getSize(Graph G);

//returns the most recently used source vertex of graph G
int getSource(Graph G);

//will return the parent of vertex u in the Breadth-First tree created by BFS(), or NIL
//if either u has no parent or BFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getParent(Graph G, int u);

//returns the distance from the most recent BFS source to vertex u, or INF if
//either u is not reachable from the source or if BFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getDist(Graph G, int u);

//appends to the List L the vertices of a shortest path in G from source to u, or 
//appends to L the value NIL if no such path exists. getPath() has the precondition
//getSource(G)!=NIL, so BFS() must be called before getPath()
//Pre: u between 1 and getOrder(G)
void getPath(List L, Graph G, int u);

/*** Manipulation procedures***/

//deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G);

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of
//v, and v to the adjacency List of u (maintaining both lists in sorted order).
//Pre: u and v between 1 and getOrder(G)
void addEdge(Graph G, int u, int v);

//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of
//u (but not u to the adjacency List of v). 
//Pre: u and v between 1 and getOrder(G)
void addArc(Graph G, int u, int v);

//runs the BFS algorithm on the Graph G with source s, setting the color, distance,
//parent, and source fields of G accordingly.
void BFS(Graph G, int s);

/*** Other operations***/

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif
