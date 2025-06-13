#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include "cell.h"

int main()
{
	rm rman;
	im iman;
	cm cman;
	map city;
	splitter(&city, "test.csv", &rman, &iman, &cman); 
	
	for(int i = 0; i < rman.numRes; i++)
	{
		printf("res %d: %d, pos: (%d, %d)\n", i, rman.rStore[i].numRes, rman.rStore[i].position.x, rman.rStore[i].position.y);
	}
	
	for(int i = 0; i < iman.numInd; i++)
	{
		printf("ind %d: %d, pos: (%d, %d)\n", i, iman.iStore[i].numInd, iman.iStore[i].position.x, iman.iStore[i].position.y);
	}

	for(int i = 0; i < cman.numCom; i++)
	{
		printf("com %d: %d, pos: (%d, %d)\n", i, cman.cStore[i].numCom, cman.cStore[i].position.x, cman.cStore[i].position.y);
	}


	for(int i = 0; i < city.rows; i++)
	{
		for(int j = 0; j < city.cols; j++)
		{
			printf("%c ", city.m[i][j]);
		}
		printf("\n");
	}
	
return 0;
}
