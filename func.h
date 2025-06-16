#ifndef FUNC_H
#define FUNC_H
#include <stdlib.h>
#include <stdio.h>
#include "cell.h"
#include "graph.h"


void addRes(rm* manager);
void addInd(im* manager);
void addCom(cm* manager);
void splitter(map* city, char filename[], rm* rman, im* iman, cm* cman);
void resChecker(rm* rMan, graph* g, map* city, im* iMan, cm* cMan);
void printMap(map* city);
int getResIndex(rm* manager, int x, int y);
int getIndIndex(im* manager, int x, int y);
int getComIndex(cm* manager, int x, int y);
void updateMap(map* ogCity, map* city, rm* rMan, im* iMan, cm* cMan);

#endif
