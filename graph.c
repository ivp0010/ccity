#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "cell.h"


p decoder(int index, int* row_lengths, int num_rows) {
    p temp;
    int i = 0;
    int original_index = index;

    while (i < num_rows && index >= row_lengths[i]) {
        index -= row_lengths[i];
        i++;
    }

    if (i >= num_rows) {
        fprintf(stderr, "decoder(): index %d ran past row count\n", original_index);
        exit(1);
    }

    printf("decoder: original_index = %d → x = %d, y = %d (row %d, col %d)\n",
           original_index, index, i, i, row_lengths[i]);

    temp.y = i;
    temp.x = index;
    return temp;
}

int encoder(int x, int y, int* row_lengths)
{
    int index = 0;
    for (int i = 0; i < y; i++) {
        index += row_lengths[i];  // add up lengths of previous rows
    }
    index += x;
    return index;
}

int findCellIndex(map* city, int x, int y)
{
    if (y < 0 || y >= city->rows) return -1;
    if (x < 0 || x >= city->colLen[y]) return -1;

    int index = x;
    for (int i = 0; i < y; i++) {
        index += city->colLen[i];
    }
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
		int directions[8][2] = {{0,  1}, { 0, -1}, { 1,  0}, {-1,  0}, { 1,  1}, {-1,  1}, { 1, -1}, {-1, -1}};
		int neb[8] = {-1, -1, -1, -1, -1, -1, -1, -1};	
		int count = 0;
		for(int j = 0; j < 8; j++)
		{
			int nx = temp.x + directions[j][0];
			int ny = temp.y + directions[j][1];

			int adjID = findCellIndex(city, nx, ny);

			if(adjID != -1)
			{					
				count++;
				neb[count - 1] = adjID;
			}	
		}
		g->sizes[i] = count;
		g->adjMat[i] = (int*)malloc(count * sizeof(int));
		for(int j = 0; j < count; j++)
		{
			g->adjMat[i][j] = neb[j];
		}
			
	}
		
}
