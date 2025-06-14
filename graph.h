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

p decoder(int index, int col)
{
	p temp;
	temp.x = index % col;
	temp.y = index / col;
	return temp;
}

void makeGraph(graph* g, int r, int c, map* city)
{
	g->adjMat = (int**)malloc((r * c)  * sizeof(int*));
	g->sizes = (int*)malloc((r * c) * sizeof(int));
	for(int i = 0; i < r*c; i++)
	{
		p temp = decoder(i, c);
		printf("(%d, %d)\n", temp.x, temp.y);
		if(temp.y == 0)
		{
			if(temp.x != 0 && temp.x != c - 1)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - 1;
				g->adjMat[i][1] = i + 1;
				g->adjMat[i][2] = i + (c - 1);
				g->adjMat[i][3] = i + c;
				g->adjMat[i][4] = i + (c + 1);
				g->sizes[i] = 5;
				continue;
			}
			else if(temp.x == 0)
			{
				g->adjMat[i] = (int*)malloc(3 * sizeof(int));
				g->adjMat[i][0] = i + 1;
				g->adjMat[i][1] = i + c;
				g->adjMat[i][2] = i + (c + 1);
				g->sizes[i] = 3;
				continue;
			}
			else
			{
				g->adjMat[i] = (int*)malloc(3 * sizeof(int));
				g->adjMat[i][0] = i - 1;
				g->adjMat[i][1] = i + (c - 1);
				g->adjMat[i][2] = i + c;
				g->sizes[i] = 3;
				continue;
			}
		}
		else if(temp.y == r - 1)
		{
			if(temp.x != 0 && temp.x != c - 1)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - 1;
				g->adjMat[i][1] = i + 1;
				g->adjMat[i][2] = i - (c - 1);
				g->adjMat[i][3] = i - c;
				g->adjMat[i][4] = i - (c + 1);
				g->sizes[i] = 5;
				continue;
			}
			else if(temp.x == 0)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i + 1;
				g->adjMat[i][1] = i - (c - 1);
				g->adjMat[i][2] = i - c;
				g->sizes[i] = 3;
				continue;
			}
			else
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - 1;
				g->adjMat[i][1] = i - c;
				g->adjMat[i][2] = i - (c + 1);
				g->sizes[i] = 3;
				continue;
			}
		}
		else
		{
			if(temp.x == 0)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - c;
				g->adjMat[i][1] = i - (c - 1);
				g->adjMat[i][2] = i + 1;
				g->adjMat[i][3] = i + c;
				g->adjMat[i][4] = i + (c + 1);
				g->sizes[i] = 5;
				continue;
			}
			else if(temp.x == c - 1)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - (c + 1);
				g->adjMat[i][1] = i - c;
				g->adjMat[i][2] = i - 1;
				g->adjMat[i][3] = i + (c - 1);
				g->adjMat[i][4] = i + c;
				g->sizes[i] = 5;
				continue;
			}
			else
			{
				g->adjMat[i] = (int*)malloc(8 * sizeof(int));
				g->adjMat[i][0] = i - (c + 1);
				g->adjMat[i][1] = i - c;
				g->adjMat[i][2] = i - (c - 1);
				g->adjMat[i][3] = i - 1;
				g->adjMat[i][4] = i + 1;
				g->adjMat[i][5] = i + (c - 1);
				g->adjMat[i][6] = i + c;
				g->adjMat[i][7] = i + (c + 1);
				g->sizes[i] = 8;
				continue;
			}
		}
	}

	
}

#endif

