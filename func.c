#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "func.h"
#include "cell.h"

void addRes(rm* manager)
{
	manager->numRes = manager->numRes + 1;
	manager->rStore = (res*)realloc(manager->rStore, manager->numRes * sizeof(res));
}

void addInd(im* manager)
{
	manager->numInd = manager->numInd + 1;
	manager->iStore = (ind*)realloc(manager->iStore, manager->numInd * sizeof(ind));
}

void addCom(cm* manager)
{
	manager->numCom = manager->numCom + 1;
	manager->cStore = (com*)realloc(manager->cStore, manager->numCom * sizeof(com));
}

void splitter(map* city, char filename[], rm* rman, im* iman, cm* cman)
{
	FILE* fp = fopen(filename, "r");
	int ch;
	int lines = 0;
	int lineSize = 0;
	while((ch = fgetc(fp)) != EOF)
	{	
		if(ch == '\n')
		{
			lines++;
		}
		else if(lines == 0 && ch != ',')
		{
			lineSize++;
		}

	}

	city->rows = lines;
	city->cols = lineSize;
	fclose(fp);
	city->m = (cell**)malloc(lines * sizeof(cell*));
	for(int i = 0; i < lines; i++)
	{
		city->m[i] = (cell*)malloc(lineSize * sizeof(cell));
	}
	fp = fopen(filename, "r");
	unsigned int x = 0;
	unsigned int y = 0;
	while((ch = fgetc(fp)) != EOF)
	{

		if(ch == 'r')
		{		
			addRes(rman);
			rman->rStore[rman->numRes - 1].position.x = x;
			rman->rStore[rman->numRes - 1].position.y = y;
		}
		if(ch == 'i')
		{
			addInd(iman);
			iman->iStore[iman->numInd - 1].position.x = x;
			iman->iStore[iman->numInd - 1].position.y = y;
		}
		if(ch == 'c')
		{
			addCom(cman);
			cman->cStore[cman->numCom - 1].position.x = x;
			cman->cStore[cman->numCom - 1].position.y = y;
		}
		if(ch != ',')
		{
			if(ch != '\n'){city->m[y][x].type = ch;}
			x++;
		}
		if(ch == '\n')
		{
			y++;
			x = 0;
		}
	}
}
