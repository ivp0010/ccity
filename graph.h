#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "func.h"

typedef struct
{
	int** adjMat;
	int* sizes;	
}graph;
p decoder(int index, int col);
void makeGraph(graph* g, int r, int c, map* city);

#endif

