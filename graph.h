#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"


typedef struct graph
{
	int** adjMat;
	int* sizes;
	char* type;
}graph;

p decoder(int index, int col);
int incoder(int x, int y, int col);
void makeGraph(graph* g, int r, int c, map* city);

#endif

