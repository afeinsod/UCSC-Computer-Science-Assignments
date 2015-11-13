##Alix Feinsod
##CruzID: afeinsod
##Class: CMPS 12B/M
##File Name: Makefile
##File's Role:  A makefile: make builds Calc.class, make test builds and runs CalcTest.class

JAVASRC = Calc.java CalcTest.java
SOURCES = README makefile ${JAVASRC}
MAINCLASS = Calc
CLASSES = Calc.class CalcTest.class
JARFILE = Calc
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

test: 
	javac -cp "junit-4.12-beta-1.jar:hamcrest-core-1.3.jar:." CalcTest.java
	java -cp "junit-4.12-beta-1.jar:hamcrest-core-1.3.jar:." org.junit.runner.JUnitCore CalcTest

.PHONY: clean all

.PHONY: test
