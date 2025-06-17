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
	map city;
	char* name = "test.csv";
	splitter(&city, name, &rMan, &iMan, &cMan);
	printMap(&city);
	map changeMap = city;
	graph g;
	queue q = {.head = NULL, .tail = NULL, .size = 0};
	makeGraph(&g, city.rows, city.cols, &changeMap);
	

	for(int i = 0; i < 5; i++)
	{
		resChecker(&rMan, &g, &changeMap, &iMan, &cMan);
		resolver(&g, &city, &rMan, &iMan, &cMan, &q);
		updateMap(&q, &city, &changeMap, &rMan, &iMan, &cMan);
		printMap(&changeMap);
	}
	
return 0;
}
