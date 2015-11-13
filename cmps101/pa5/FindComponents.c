//Alix Feinsod
//afeinsod
//CMPS 101 PA5
//FindComponents.c - program to find the connected components of a graph

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   	FILE *in, *out;
   	char line[MAX_LEN];

   //checks for correct usage
        if( argc != 3 ){
      		printf("Usage: FindPath <input file> <output file>\n");
      		exit(1);
   	} 

       	else {
	// Open files for reading and writing
            in = fopen(argv[1], "r");
	    out = fopen(argv[2], "w");
   	    if( in==NULL ){
      		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   	    }
   	    if( out==NULL ){
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
	    }

	
	fgets(line, MAX_LEN, in);
	int o;
	sscanf(line, " %d ", &o);
	
	//creates a new graph with order from first line of file
	Graph G;
	G= newGraph(o);

	//adds edges to G, then prints to output file
	int x, y;
	fgets(line, MAX_LEN, in);
	sscanf(line, " %d %d ", &x, &y);
	while ((x != 0) || (y != 0)) {
	        addArc(G, x, y);
		fgets(line, MAX_LEN, in);
		sscanf(line, " %d %d ", &x, &y);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");
	//Creates and fills list L
	List L;
	L=newList();
	for (int i = 1; i <= getOrder(G); i++) {
		append(L, i);
	}
	//runs DFS on G and L
	DFS(G,L);
	//creates new graph for transpose of G
	Graph T;
	T = transpose(G);
	//runs DFS on transpose of G
	DFS(T,L);
	
	//prints output
	fprintf(out, "G contains %d strongly connected components:\n", getgcc(T));
	for (int i =1; i<= getgcc(T); i++) {
		fprintf(out, "Component %d:", i);
		moveTo(L, 0);
		while(getIndex(L) > -1){
			if (getcc(T, getElement(L)) == i){
				fprintf(out, " %d", getElement(L));
			}
			moveNext(L);
		}
		fprintf(out, "\n");
	}
	
	freeList(&L);	
	//closes input and output files
            fclose(in);
            fclose(out);
	//frees everything
	    freeGraph(&G);
	    freeGraph(&T);
	    return(0);
	}
}
