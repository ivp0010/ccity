#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "func.h"
#include "cell.h"

void addRes(rm* manager)
{
	manager->numRes = manager->numRes + 1;
	manager->rStore = (res*)realloc(manager->rStore, manager->numRes * sizeof(res));
	manager->rStore[manager->numRes - 1].toInc = false;
}

void addInd(im* manager)
{
	manager->numInd = manager->numInd + 1;
	manager->iStore = (ind*)realloc(manager->iStore, manager->numInd * sizeof(ind));
	manager->iStore[manager->numInd - 1].toInc = false;
}

void addCom(cm* manager)
{
	manager->numCom = manager->numCom + 1;
	manager->cStore = (com*)realloc(manager->cStore, manager->numCom * sizeof(com));
	manager->cStore[manager->numCom - 1].toInc = false;
}

int getResIndex(rm* manager, int x, int y)
{
	for(int i = 0; i < manager->numRes; i++)
	{
		if(manager->rStore[i].position.x == x && manager->rStore[i].position.y == y)
		{
			return i;
		}
	}
return -1;
}

int getIndIndex(im* manager, int x, int y)
{
	for(int i = 0; i < manager->numInd; i++)
	{
		if(manager->iStore[i].position.x == x && manager->iStore[i].position.y == y)
		{
			return i;
		}
	}
return -1;
}

int getComIndex(cm* manager, int x, int y)
{
	for(int i = 0; i < manager->numCom; i++)
	{
		if(manager->cStore[i].position.x == x && manager->cStore[i].position.y == y)
		{
			return i;
		}
	}
return -1;
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

int getAdjPop(graph* g,int index, int cols, rm* rMan, im* iMan, cm* cMan, int num)
{
	char type;
	int pop = 0;
	for(int i = 0; i < g->sizes[i]; i++)
	{	
		type = g->type[g->adjMat[index][i]];
		if(type == 'r' || type == 'i' || type == 'c')
		{
			switch(type)
			{
				case 'r': 
				{
					p temp = decoder(i , cols);
					int idx = getResIndex(rMan, temp.x, temp.y);
					if(rMan->rStore[idx].numRes >= num){pop++;}
					break;
				}
				case 'i': 
				{	
					p temp = decoder(i , cols);
					int idx = getIndIndex(iMan, temp.x, temp.y);
					if(iMan->iStore[idx].numInd >= num){pop++;}
					break;
				}
				case 'c': 
				{	
					p temp = decoder(i , cols);
					int idx = getComIndex(cMan, temp.x, temp.y);
					if(cMan->cStore[idx].numCom >= num){pop++;}
					break;
				}
			}
		}
	}
return pop;
}

void resChecker(rm* rMan, graph* g, map* city, im* iMan, cm* cMan) 
{
	for(int i = 0; i < (city->rows * city->cols); i++)
	{
		if(g->type[i] != 'r'){continue;}
		p temp = decoder(i, city->cols);
		int idx = getResIndex(rMan, temp.x, temp.y);
	
		switch(rMan->rStore[idx].numRes)
		{
			case 0:	
			{
				for(int j = 0; j < g->sizes[i]; j++)
				{
					if(g->type[g->adjMat[i][j]] == 'T')			
					{
						rMan->rStore[idx].toInc = true;
						break;
					}
				}
				if(getAdjPop(g, i, city->cols, rMan, iMan, cMan, 1) > 0)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;	
			}
			case 1:
			{
				if(getAdjPop(g, i, city->cols, rMan, iMan, cMan, 1) > 1)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}	
			break;
			}
			case 2:
			{
				if(getAdjPop(g, i, city->cols, rMan, iMan, cMan, 2) > 3)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;
			}
			case 3:
			{
				if(getAdjPop(g, i, city->cols, rMan, iMan, cMan, 3) > 5)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;
			}
			case 4:
			{
				if(getAdjPop(g, i, city->cols, rMan, iMan, cMan, 4) > 7)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;
			}
		}
	}
}

void printMap(map* city)
{
	for(int i = 0; i < city->rows; i++)
	{
		for(int j = 0; j < city->cols; j++)
		{
			printf("%c ", city->m[i][j].type);
		}
		printf("\n");
	}	
}

void updateMap(map* ogCity, map* city, rm* rMan, im* iMan, cm* cMan)
{
	for(int i = 0; i < city->rows * city->cols; i++)
	{
		p temp = decoder(i, city->cols);
		switch(ogCity->m[temp.y][temp.x].type)
		{
			case 'r':
			{
				int idx = getResIndex(rMan, temp.x, temp.y);
				if(rMan->rStore[idx].toInc == true)
				{
					rMan->rStore[idx].toInc = false;
					rMan->rStore[idx].numRes += 1;
					city->m[temp.y][temp.x].type = '0' + rMan->rStore[idx].numRes;
					break;
				}
			break;
			}
			case 'i':
			{
				int idx = getIndIndex(iMan, temp.x, temp.y);
				if(iMan->iStore[idx].toInc == true)
				{
					iMan->iStore[idx].toInc = false;
					iMan->iStore[idx].numInd += 1;
					city->m[temp.y][temp.x].type = '0' + iMan->iStore[idx].numInd;
					break;
				}
			break;	
			}
			case 'c':
			{
				int idx = getComIndex(cMan, temp.x, temp.y);
				if(cMan->cStore[idx].toInc == true)
				{
					cMan->cStore[idx].toInc = false;
					cMan->cStore[idx].numCom += 1;
					city->m[temp.y][temp.x].type = '0' + cMan->cStore[idx].numCom;
					break;
				}
			break;
			}
		}
	}
}
