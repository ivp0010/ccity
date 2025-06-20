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

p decoder(int index, int* row_lengths, int num_rows);
int encoder(int x, int y, int* row_lengths);
int findCellIndex(map* city, int x, int y);
void makeGraph(graph* g, map* city);

#endif

