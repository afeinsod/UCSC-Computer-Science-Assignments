## Alix Feinsod
##CruzID: afeinsod
##Class: CMPS 12B/M
##Makefile
##Makefile for Lab 5

CC = gcc -Wall -g -std=c99 
CFLAGS = -std=c99 -Wall -Werror -Wfatal-errors -g
OBJS = list.c
OUTPUT = list
HEADERS = minunit.h

${OUTPUT}: ${OBJS}
	${CC} $< -o ${OUTPUT}

clean:
	rm -f *.o

spotless: clean
	rm -f ${OUTPUT}

test: ${OUTPUT}
	valgrind ./${OUTPUT}

.PHONY: clean spotless test
