#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "cell.h"

p decoder(int index, int* row_lengths, int num_rows)
{
    p temp;
    int i = 0;
    while (i < num_rows && index >= row_lengths[i]) {
        index -= row_lengths[i];
        i++;
    }
    temp.y = i;
    temp.x = index;
    return temp;
}


int incoder(int x, int y, int* row_lengths)
{
    int index = 0;
    for (int i = 0; i < y; i++) {
        index += row_lengths[i];  // add up lengths of previous rows
    }
    index += x;
    return index;
}


void makeGraph(graph* g, map* city)
{
	g->adjMat = (int**)malloc(city->mapSize  * sizeof(int*));
	g->sizes = (int*)malloc(city->mapSize * sizeof(int));
	g->type = (char*)malloc(city->mapSize * sizeof(char));
	for(int i = 0; i < city->mapSize; i++)
	{
		p temp = decoder(i, city->colLen, city->rows);
		g->type[i] = city->m[temp.y][temp.x].type;
		if(temp.y == 0)
		{
			if(temp.x != 0 && temp.x != c - 1)
			{
				g->adjMat[i] = (int*)malloc(5 * sizeof(int));
				g->adjMat[i][0] = i - 1;
				g->adjMat[i][1] = i + 1;
				g->adjMat[i][2] = i + (city->colLen[i] - 1);
				g->adjMat[i][3] = i + city->colLen[i];
				g->adjMat[i][4] = i + (city->colLen[i] + 1);
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
