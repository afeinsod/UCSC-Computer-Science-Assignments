//Alix Feinsod
//afeinsod
//CMPS 101 PA4
//FindPath.c - program to do Graph algorithms

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
	        addEdge(G, x, y);
		fgets(line, MAX_LEN, in);
		sscanf(line, " %d %d ", &x, &y);
	}
	printGraph(out, G);
	fprintf(out, "\n");
	List L;
	L=newList();
	//runs DFS on G for the rest of the values
	while (fgets(line, MAX_LEN, in) != NULL) {
		sscanf(line, " %d %d ", &x, &y);
		if ((x != 0) || (y!=0)) {
		    BFS(G, x);
		    if (getDist(G, y) == -1) {
			fprintf(out, "The distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists", x, y);
		    }
		    else {
			fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G,y));
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			clear(L);
			getPath(L, G, y);
			printList(out, L);
			fprintf(out, "\n");
		    }
		    fprintf(out, "\n");
		}
	} 
	freeList(&L);	
	//closes input and output files
            fclose(in);
            fclose(out);
	//frees everything
	    freeGraph(&G);
	    return(0);
	}
}
