#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include "cell.h"
#include "graph.h"
int main()
{
	rm rman = {.numRes = 0};
	im iman = {.numInd = 0};
	cm cman = {.numCom = 0};
	map city;
	splitter(&city, "test.csv", &rman, &iman, &cman); 
	graph g;
	makeGraph(&g, city.rows, city.cols, &city);
	



return 0;
}

