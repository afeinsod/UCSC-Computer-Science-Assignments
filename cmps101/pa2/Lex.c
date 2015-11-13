//Alix Feinsod
//afeinsod
//CMPS 101 PA2
//Lex.c - program to alphabetize files

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   	FILE *in, *out;
   	char line[MAX_LEN];

   //checks for correct usage
        if( argc != 3 ){
      		printf("Usage: Lex <input file> <output file>\n");
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

	// reads file to get number of lines
            int lines = 0;
            while( fgets(line, MAX_LEN, in) != NULL) {
                lines++;
            }
            fclose(in);
	
	//creates an array of Strings
	    char **S = malloc(lines * sizeof(char *));
	    lines = 0;

	//reopens the file to read in the lines
            in = fopen(argv[1], "r");

        //Adds all lines of input file to list of strings.
            while( fgets(line, MAX_LEN, in) != NULL) {
	      S[lines] = malloc(sizeof(line));
	      strcpy(S[lines], line);
	      lines++;
   	    }

	//sorting into indexList
            List L = newList();
	    append(L, 0);
            for (int i = 1; i < lines; i ++) {
	    
		moveTo(L, 0);
		while ((getIndex(L) >= 0) && (strcmp(S[getElement(L)],S[i])<0)) {
		        
			moveNext(L);
		}
		if (getIndex(L) < 0) {
			append(L, i);
		}
		else {
		        insertBefore(L,i);
		}
	    }

        //prints lines to doc
	    fprintf(out, "%s \n", S[front(L)]);
	    free(S[front(L)]);
            for(moveTo(L, 1); getIndex(L)>=0; moveNext(L)){
	      fprintf(out, "%s", S[getElement(L)]);
	      free(S[getElement(L)]);
	    }
	//closes input and output files
            fclose(in);
            fclose(out);
	//frees everything

	    free(S);
	    freeList(&L);
	    return(0);
	}
}
