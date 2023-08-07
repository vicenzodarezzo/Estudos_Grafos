all: graph.o main.o
	gcc *.o -o main -std=c99 -Wall

graph.o:
	gcc -c graph.c -o graph.o

main.o:
	gcc -c main.c -o main.o

make run:
	./main

clean:
	rm *.o main
