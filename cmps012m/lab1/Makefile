
##Alix Feinsod
##CruzID: afeinsod
##Class: CMPS 12B/M
##File Name: Makefile
##File's Role:  A simple makefile with variables

JAVASRC = hello.java hello2.java
SOURCES = README makefile ${JAVASRC}
MAINCLASS = hello2
CLASSES = hello.class hello2.class
JARFILE = myHello
JARCLASSES = ${CLASSES}

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo "Main-class: ${MAINCLASS}" > Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	rm Manifest
	chmod +x ${JARFILE}

${CLASSES}: ${JAVASRC}
	javac -Xlint ${JAVASRC}

clean:
	rm ${CLASSES} ${JARFILE}

.PHONY: clean all

