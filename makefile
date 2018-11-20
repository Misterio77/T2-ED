all: PCC

PCC: main.o list.o  tree.o node.o
	gcc -o PCC main.o list.o  tree.o node.o -lm

list.o: list.c
	gcc -o list.o -c list.c -g -Wall

node.o: node.c
	gcc -o node.o -c node.c -g -Wall

tree.o: tree.c
	gcc -o tree.o -c tree.c -g -Wall

main.o: main.c list.h 
	gcc -o main.o -c main.c -g -Wall

clean:
	rm -f *.o PCC
