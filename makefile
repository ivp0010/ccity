
CC = gcc
CFLAGS = -Wall -Wextra -g


TARGET = ccity

OBJS = main.o func.o graph.o queue.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.c cell.h func.h graph.h queue.h
	$(CC) $(CFLAGS) -c main.c

func.o: func.c cell.h func.h graph.h queue.h
	$(CC) $(CFLAGS) -c func.c

graph.o: graph.c graph.h func.h cell.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
