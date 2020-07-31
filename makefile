all: edge

edge: main.o cvision.o
	gcc -g -std=c99 -o edge main.o cvision.o -lm

cvision.o: cvision.c cvision.h
	gcc -g -std=c99 -o cvision.o cvision.c -c -lm

main.o: main.c
	gcc -g -std=c99 -o main.o main.c -c

clean: 
	-rm -rf *.o *~
