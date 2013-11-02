CCFLAGS = -ansi -Wall -pedantic -g
CC = gcc

all: search

search: FreqList.o prefixTree.o WordTree.o main.o
	${CC} ${CCFLAGS} -o search main.o FreqList.o prefixTree.o WordTree.o

main.o:
	${CC} ${CCFLAGS} -c main.c

FreqList.o:
	${CC} ${CCFLAGS} -c FreqList.c

prefixTree.o:
	${CC} ${CCFLAGS} -c prefixTree.c

WordTree.o:
	${CC} ${CCFLAGS} -c WordTree.c

clean:
	rm -f *o *gch search
