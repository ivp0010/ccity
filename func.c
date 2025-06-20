#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "func.h"
#include "cell.h"
#include "queue.h"

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
	manager->iStore[manager->numInd - 1].priority = 0;
}

void addCom(cm* manager)
{
	manager->numCom = manager->numCom + 1;
	manager->cStore = (com*)realloc(manager->cStore, manager->numCom * sizeof(com));
	manager->cStore[manager->numCom - 1].toInc = false;
	manager->cStore[manager->numCom - 1].priority = 0;
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
			if(sizeof(city->colLen) == 0)
			{
				city->colLen = (int*)malloc(sizeof(int));
				city->colLen[lines - 1] = lineSize;
				lineSize = 0;
			}
			else
			{
				city->colLen = (int*)realloc(city->colLen ,lines * sizeof(int));
				city->colLen[lines - 1] = lineSize;
				lineSize = 0;
			}
		}
		else if(ch != ',')
		{
			lineSize++;
		}

	}

	fclose(fp);

	city->m = (cell**)malloc(lines * sizeof(cell*));
	city->index = (p**)malloc(lines * sizeof(p*));
	for(int i = 0; i < lines; i++)
	{
		city->m[i] = (cell*)malloc(city->colLen[i] * sizeof(cell));
		city->index[i] = (p*)malloc(city->colLen[i] * sizeof(p));
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
			p temp;
			temp.x = x;
			temp.y = y;
			city->index[y][x] = temp;
		}
		if(ch == 'i')
		{
			addInd(iman);
			iman->iStore[iman->numInd - 1].position.x = x;
			iman->iStore[iman->numInd - 1].position.y = y;
			p temp;
			temp.x = x;
			temp.y = y;
			city->index[y][x] = temp;

		}
		if(ch == 'c')
		{
			addCom(cman);
			cman->cStore[cman->numCom - 1].position.x = x;
			cman->cStore[cman->numCom - 1].position.y = y;
			p temp;
			temp.x = x;
			temp.y = y;
			city->index[y][x] = temp;

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

int getAdjPop(graph* g, int index, map* city, rm* rMan, im* iMan, cm* cMan, int num)
{
	char type;
	int pop = 0;
	for(int i = 0; i < g->sizes[index]; i++)
	{	
		type = g->type[g->adjMat[index][i]];
		if(type == 'r' || type == 'i' || type == 'c')
		{
			switch(type)
			{
				case 'r': 
				{
					printf("%d\n", g->adjMat[index][i]);
					p temp = decoder(g->adjMat[index][i] , city->colLen, city->rows);
					printf("i = %d\n", i);
					int idx = getResIndex(rMan, temp.x, temp.y);
					if(rMan->rStore[idx].numRes >= num){pop++;}
					break;
				}
				case 'i': 
				{	
					p temp = decoder(g->adjMat[index][i] , city->colLen, city->rows);
					int idx = getIndIndex(iMan, temp.x, temp.y);
					if(iMan->iStore[idx].numInd >= num){pop++;}
					break;
				}
				case 'c': 
				{	
					p temp = decoder(g->adjMat[index][i] , city->colLen, city->rows);
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
	for(int i = 0; i < city->mapSize; i++)
	{
		if(g->type[i] != 'r'){continue;}
		p temp = decoder(i, city->colLen, city->rows);
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
				if(getAdjPop(g, i, city->colLen[i], rMan, iMan, cMan, 1) > 0)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;	
			}
			case 1:
			{
				if(getAdjPop(g, i, city->colLen[i], rMan, iMan, cMan, 1) > 1)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}	
			break;
			}
			case 2:
			{
				if(getAdjPop(g, i, city->colLen[i], rMan, iMan, cMan, 2) > 3)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;
			}
			case 3:
			{
				if(getAdjPop(g, i, city->colLen[i], rMan, iMan, cMan, 3) > 5)
				{
					rMan->rStore[idx].toInc = true;
					break;
				}
			break;
			}
			case 4:
			{
				if(getAdjPop(g, i, city->colLen[i], rMan, iMan, cMan, 4) > 7)
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
		for(int j = 0; j < city->colLen[i]; j++)
		{
			printf("%c  ", city->m[i][j].type);
		}
		printf("\n\n");
	}	
}

int getNumWorkers(rm* manager)
{
	int count = 0;
	for(int i = 0; i < manager->numRes; i++)
	{
		for(int j = 0; j < manager->rStore[i].numRes; j++)
		{
			if(manager->rStore[i].isEmp[i] == false)
			{
				count++;
			}
		}
	}
	return count;
}

void updateMap(queue* q, map* ogCity, map* city, rm* rMan, im* iMan, cm* cMan)
{

	while(q->size != 0)
	{
		typeIdx temp = pop(q);
		if(temp.type == 'c')
		{
			if(getNumWorkers(rMan) < 1){continue;}
			cMan->cStore[temp.index].toInc = true;
			getWorkers(1, rMan);
		}
		else if(temp.type == 'i')
		{
			if(getNumWorkers(rMan) < 2){continue;}
			iMan->iStore[temp.index].toInc = true;
			getWorkers(2, rMan);
		}

	}

	for(int i = 0; i < city->mapSize; i++)
	{
		p temp = decoder(i, city->colLen, city->rows);
		switch(ogCity->m[temp.y][temp.x].type)
		{
			case 'r':
			{
				int idx = getResIndex(rMan, temp.x, temp.y);
				if(rMan->rStore[idx].toInc == true)
				{
					rMan->rStore[idx].toInc = false;
					rMan->rStore[idx].numRes += 1;
					if(rMan->rStore[idx].numRes == 1)
					{
						rMan->rStore[idx].isEmp = (bool*)malloc(sizeof(bool));
					}
					else
					{
						rMan->rStore[idx].isEmp = (bool*)realloc(rMan->rStore[idx].isEmp, rMan->rStore[idx].numRes * sizeof(bool));
					}
					rMan->rStore[idx].isEmp[rMan->rStore[idx].numRes - 1] = false; 
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

void getWorkers(int num, rm* manager)
{
	int count = 0;
	for(int i = 0; i < manager->numRes; i++)
	{
		for(int j = 0; j < manager->rStore[i].numRes; j++)
		{
			if(manager->rStore[i].isEmp[j] == false)
			{
				manager->rStore[i].isEmp[j] = true;
				count++;
				if(num == count){return;}
			}
		}
	}

}

int getTotalPop(graph* g, map* city, int index, rm* rMan, im* iMan, cm* cMan)
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
					p temp = decoder(i , city->colLen, city->rows);
					int idx = getResIndex(rMan, temp.x, temp.y);
					pop += rMan->rStore[idx].numRes;
					break;
				}
				case 'i': 
				{	
					p temp = decoder(i , city->colLen, city->rows);
					int idx = getIndIndex(iMan, temp.x, temp.y);
					pop += iMan->iStore[idx].numInd;
					break;
				}
				case 'c': 
				{	
					p temp = decoder(i , city->colLen, city->rows);
					int idx = getComIndex(cMan, temp.x, temp.y);
					pop += cMan->cStore[idx].numCom;
					break;
				}
			}
		}
	}
return pop;
}


void resolver(graph* g, map* city, rm* rMan, im* iMan, cm* cMan, queue *q)
{	
	//commercial
	int* canInc;
	int size = 0;
	for(int i = 0; i < city->mapSize; i++)
	{
		if(g->type[i] != 'c'){continue;}
		p temp = decoder(i, city->colLen, city->rows);
		int idx = getComIndex(cMan, temp.x, temp.y);
	
		switch(cMan->cStore[idx].numCom)
		{
			case 0:	
			{
				for(int j = 0; j < g->sizes[i]; j++)
				{
					if(g->type[g->adjMat[i][j]] == 'T')			
					{
						if(size == 0){canInc = (int*)malloc(sizeof(int));}
						else{canInc = (int*)realloc(canInc, sizeof(int) * size + 1);}
						size++;
						canInc[size - 1] = idx;
						break;
					}
				}
				if(getAdjPop(g, i, city, rMan, iMan, cMan, 1) > 0)
				{
					if(size == 0){canInc = (int*)malloc(sizeof(int));}
					else{canInc = (int*)realloc(canInc, sizeof(int) * size + 1);}
					size++;
					canInc[size - 1] = idx;
					break;
				}
			break;	
			}
			case 1:
			{
				if(getAdjPop(g, i, city, rMan, iMan, cMan, 1) > 1)
				{
					if(size == 0){canInc = (int*)malloc(sizeof(int));}
					else{canInc = (int*)realloc(canInc, sizeof(int) * size + 1);}
					size++;
					canInc[size - 1] = idx;
					cMan->cStore[canInc[size - 1]].priority += 1000;
					break;
				}
			break;
			}
		}
	}
		bool swap;	
		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(getTotalPop(g, canInc[i], city, rMan, iMan, cMan) < getTotalPop(g, canInc[j], city, rMan, iMan, cMan))
				{
					int temp = canInc[i];
					canInc[i] = canInc[j];
					canInc[j] = temp;
					swap = true;
				}
			}
			if(!swap){break;}
		}
	
		for(int i = 0; i < size; i++)
		{
			if(getTotalPop(g, canInc[i], city, rMan, iMan, cMan) == getTotalPop(g, canInc[i - 1], city, rMan, iMan, cMan) && i != 0)
			{
				cMan->cStore[canInc[i]].priority += cMan->cStore[canInc[i - 1]].priority;
				continue;
			}

			cMan->cStore[canInc[i]].priority += 100 - (10 * i);
		}

		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(cMan->cStore[canInc[i]].position.y < cMan->cStore[canInc[j]].position.y)
				{
					int temp = canInc[i];
					canInc[i] = canInc[j];
					canInc[j] = temp;
					swap = true;	
				}
			}
			if(!swap){break;}
		}

		for(int i = 0; i < size; i++)
		{
			if(cMan->cStore[canInc[i]].position.y == cMan->cStore[canInc[i - 1]].position.y&& i != 0)
			{
				cMan->cStore[canInc[i]].priority += cMan->cStore[canInc[i]].priority;
				continue;
			}

			cMan->cStore[canInc[i]].priority += 50 - (5 * i);
		}
			
		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(cMan->cStore[canInc[i]].position.x < cMan->cStore[canInc[j]].position.x)
				{
					int temp = canInc[i];
					canInc[i] = canInc[j];
					canInc[j] = temp;
					swap = true;	
				}
			}
			if(!swap){break;}
		}

		for(int i = 0; i < size; i++)
		{
			if(cMan->cStore[canInc[i]].position.x == cMan->cStore[canInc[i - 1]].position.x && i != 0)
			{
				cMan->cStore[canInc[i]].priority += cMan->cStore[canInc[i]].priority;
				continue;
			}

			cMan->cStore[canInc[i]].priority += 10 - (1 * i);
		}
		
		for(int i = 0; i < size; i++)
		{
			push(q, canInc[i], 'c');
			cMan->cStore[canInc[i]].priority = 0;
		}
		printf("no\n");
		free(canInc);
		printf("yes\n");
		int* indInc;
		size = 0;
		//Industrial
		for(int i = 0; i < city->mapSize; i++)
		{
			if(g->type[i] != 'i'){continue;}
			p temp = decoder(i, city->colLen, city->rows);
			int idx = getIndIndex(iMan, temp.x, temp.y);
	
			switch(iMan->iStore[idx].numInd)
			{
				case 0:	
				{
					for(int j = 0; j < g->sizes[i]; j++)
					{
						if(g->type[g->adjMat[i][j]] == 'T')			
						{
							if(size == 0){indInc = (int*)malloc(sizeof(int));}
							else{indInc = (int*)realloc(indInc, sizeof(int) * size + 1);}
							size++;
							indInc[size - 1] = idx;
							break;
						}
					}
					if(getAdjPop(g, i, city, rMan, iMan, cMan, 1) > 0)
					{
						if(size == 0){indInc = (int*)malloc(sizeof(int));}
						else{indInc = (int*)realloc(indInc, sizeof(int) * size + 1);}
						size++;
						indInc[size - 1] = idx;
						break;
					}
				break;	
				}
				case 1:
				{
					if(getAdjPop(g, i, city, rMan, iMan, cMan, 1) > 1)
					{
						if(size == 0){indInc = (int*)malloc(sizeof(int));}
						else{indInc = (int*)realloc(indInc, sizeof(int) * size + 1);}
						size++;
						indInc[size - 1] = idx;
						iMan->iStore[indInc[size - 1]].priority += 500;
						break;
					}
				break;
				}
				case 2:
				{
					if(getAdjPop(g, i, city, rMan, iMan, cMan, 1) > 3)
					{
						if(size == 0){indInc = (int*)malloc(sizeof(int));}
						else{indInc = (int*)realloc(indInc, sizeof(int) * size + 1);}
						size++;
						indInc[size - 1] = idx;
						iMan->iStore[indInc[size - 1]].priority += 1000;
						break;
					}
				break;
				}
			}
		}
		
		
		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(getTotalPop(g, indInc[i], city, rMan, iMan, cMan) < getTotalPop(g, indInc[j], city, rMan, iMan, cMan))
				{
					int temp = indInc[i];
					indInc[i] = indInc[j];
					indInc[j] = temp;
					swap = true;
				}
			}
			if(!swap){break;}
		}
	
		for(int i = 0; i < size; i++)
		{
			if(getTotalPop(g, indInc[i], city, rMan, iMan, cMan) == getTotalPop(g, indInc[i - 1], city, rMan, iMan, cMan) && i != 0)
			{
				iMan->iStore[indInc[i]].priority += iMan->iStore[indInc[i - 1]].priority;
				continue;
			}

			iMan->iStore[indInc[i]].priority += 100 - (10 * i);
		}

		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(iMan->iStore[indInc[i]].position.y < iMan->iStore[indInc[j]].position.y)
				{
					int temp = indInc[i];
					indInc[i] = indInc[j];
					indInc[j] = temp;
					swap = true;	
				}
			}
			if(!swap){break;}
		}
		
		for(int i = 0; i < size; i++)
		{
			if(iMan->iStore[indInc[i]].position.y == iMan->iStore[indInc[i - 1]].position.y && i != 0)
			{
				iMan->iStore[indInc[i]].priority += iMan->iStore[indInc[i]].priority;
				continue;
			}

			iMan->iStore[indInc[i]].priority += 50 - (5 * i);
		}
			
		for(int i = 0; i < size; i++)
		{
			swap = false;
			for(int j = 0; j < size; j++)
			{
				if(iMan->iStore[indInc[i]].position.x < iMan->iStore[indInc[j]].position.x)
				{
					int temp = indInc[i];
					indInc[i] = indInc[j];
					indInc[j] = temp;
					swap = true;	
				}
			}
			if(!swap){break;}
		}

		for(int i = 0; i < size; i++)
		{
			if(iMan->iStore[indInc[i]].position.x == iMan->iStore[indInc[i - 1]].position.x && i != 0)
			{
				iMan->iStore[indInc[i]].priority += iMan->iStore[indInc[i]].priority;
				continue;
			}

			iMan->iStore[indInc[i]].priority += 10 - (1 * i);
		}
		
		for(int i = 0; i < size; i++)
		{
			push(q, indInc[i], 'i');
			iMan->iStore[indInc[i]].priority = 0;
		}
		free(indInc);
}
