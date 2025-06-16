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
	}

	q->tail->next = newNode;
	q->tail = newNode;
	newNode->next = NULL;
}

typeIdx pop(queue* q)
{
	node* temp = q->head;
	q->head = q->head->next;
	typeIdx tempTI = temp->ti;
	free(temp);
	return tempTI;
}
