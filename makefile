
main: main.o func.o graph.o
	-gcc main.o func.o graph.o -o ccity
main.o: main.c cell.h func.h graph.h
	-gcc -c main.c
func.o: func.c cell.h func.h graph.h
	-gcc -c func.c
graph.o: graph.c graph.h func.h cell.h
	-gcc -c graph.c

