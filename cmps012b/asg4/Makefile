##Alix Feinsod
##CruzID: afeinsod
##Class: CMPS 12B/M
##Makefile
##Makefile for Programming Assingment 4: Create Your Own Adventure

JAVASRC    = cyoa.java Stack.java room.java option.java
SOURCES    = ${JAVASRC} Makefile
ALLSOURCES = ${SOURCES}
MAINCLASS  = cyoa
CLASSES    = ${patsubst %.java, %.class, ${JAVASRC}}

all: ${CLASSES}

%.class: %.java
	javac -Xlint $<

clean:
	rm -f *.class ${MAINCLASS}

test: all
	java cyoa demo.adventure

.PHONY: clean all test