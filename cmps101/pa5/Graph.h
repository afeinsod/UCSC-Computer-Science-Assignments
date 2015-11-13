//-----------------------------------------------------------------------------
// Alix Feinsod
// afeinsod
// Programming Assignment 5, CMPS 101
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

//will return the parent of vertex u in the Depth-First tree created by DFS(), or NIL
//if either u has no parent or DFS() has not yet been called.
//Pre: u between 1 and getOrder(G)
int getParent(Graph G, int u);

//Returns discover time of vertex u by DFS()
//Pre: u between 1 and getOrder(G)
int getDiscover(Graph G, int u);

//Returns finish time of vertex u by DFS()
//Pre: u between 1 and getOrder(G)
int getFinish(Graph G, int u);

//returns the number of strongly connected components in G
int getgcc(Graph G);

//returns number of connected component with u as an element
//pre: u between 1 and getOrder(G)
int getcc(Graph G, int u);

/*** Manipulation procedures***/

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of
//v, and v to the adjacency List of u (maintaining both lists in sorted order).
//Pre: u and v between 1 and getOrder(G)
void addEdge(Graph G, int u, int v);

//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of
//u (but not u to the adjacency List of v). 
//Pre: u and v between 1 and getOrder(G)
void addArc(Graph G, int u, int v);

//runs the DFS algorithm on the Graph G, using the List S to order the vertices
//and store the stack of finished vertices.
//Pre: Length of S = size of G, S has all the correct numbers in it(does not check this)
void DFS(Graph G, List S);

/*** Other operations***/

//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

//Returns a reference to a new graph object that is a copy of G
Graph copyGraph(Graph G);

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif
