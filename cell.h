#ifndef CELL_H
#define CELL_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct pos
{

	int x, y;

}p;

typedef struct cell 
{
	p cords;
	char type; 

}cell;

typedef struct residential
{
	int numRes;
	bool* isEmp;
	p position;
	bool toInc;
}res;

typedef struct industrial
{
	int numInd;
	p position;
	bool toInc;
	int priority;

}ind;

typedef struct commercial
{
	int numCom;
	p position;
	bool toInc;
	int priority;

}com;

typedef struct resManager
{
	res* rStore;
	int numRes;

}rm;

typedef struct indManager
{
	ind* iStore;
	int numInd;

}im;

typedef struct comManager
{
	com* cStore;
	int numCom;

}cm;


typedef struct cmap
{
	cell** m;
	p** index;
	int rows;
	int cols;
}map;

#endif
