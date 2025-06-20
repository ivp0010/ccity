#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include "cell.h"
#include "graph.h"
#include "queue.h"

int main()
{

	rm rMan = {.numRes = 0};
	im iMan = {.numInd = 0};
	cm cMan = {.numCom = 0};
	map city = {.mapSize = 0};
	char* name = "test.csv";
	splitter(&city, name, &rMan, &iMan, &cMan);
	printf("1\n");
	printMap(&city);
	printf("2\n");
	map changeMap = city;
	graph g;
	queue q = {.head = NULL, .tail = NULL, .size = 0};
	printf("3\n");
	makeGraph(&g, &changeMap);
	printf("4\n");
	for(int i = 0; i < city.mapSize; i++)
	{
		printf("%d: ", i);
		for(int j = 0; j < g.sizes[i]; j++)
		{
			printf("%d ", g.adjMat[i][j]);
		}
		printf("\n");
	}

	
	for(int i = 0; i < 20; i++)
	{
		printf("rc\n");
		resChecker(&rMan, &g, &changeMap, &iMan, &cMan);
		printf("r\n");
		resolver(&g, &city, &rMan, &iMan, &cMan, &q);
		printf("um\n");
		updateMap(&q, &city, &changeMap, &rMan, &iMan, &cMan);
		printf("out");
	}
	printMap(&changeMap);
	
return 0;
}
