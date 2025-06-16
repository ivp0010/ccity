#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>
typedef struct typeIdx
{
	char type;
	int index;

}typeIdx;

typedef struct node
{
	typeIdx ti;
	struct node* next;

}node;

typedef struct queue
{
	node* head;
	node* tail;

}queue;

void push(queue* q, int value, char t);
typeIdx pop(queue* q);

#endif
