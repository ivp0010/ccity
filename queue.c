#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void push(queue* q, int value, char t)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->ti.index = value;
	newNode->ti.type = t;

	if(q->head == NULL)
	{
		q->head = newNode;
		q->tail = newNode;
		newNode->next = NULL;
		q->size += 1;
		return;
	}

	q->tail->next = newNode;
	q->tail = newNode;
	newNode->next = NULL;
	q->size += 1;
}

typeIdx pop(queue* q)
{
	node* temp = q->head;
	q->head = q->head->next;
	typeIdx tempTI = temp->ti;
	free(temp);
	q->size -= 1;
	return tempTI;
}
