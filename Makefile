CC=gcc
CFLAGS=-Wall -Warray-bounds
LFLAGS=-lm -lgsl -lgslcblas

all: SDE

SDE.o: SDE.c
	${CC} ${CFLAGS} ${EXTFLAGS} -c SDE.c

SDE: SDE.o 
	${CC} ${LFLAGS} SDE.o -o SDE.out
 
clean: 
	rm -f SDE.o SDE.out 
