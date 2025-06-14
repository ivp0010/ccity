
main: main.o
	-gcc main.o -o ccity
main.o: main.c cell.h func.h graph.h
	-gcc -c main.c

