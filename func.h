#ifndef FUNC_H
#define FUNC_H
#include <stdlib.h>
#include <stdio.h>
#include "cell.h"
#include "graph.h"
#include "queue.h"

void addRes(rm* manager);
void addInd(im* manager);
void addCom(cm* manager);
void splitter(map* city, char filename[], rm* rman, im* iman, cm* cman);
void resChecker(rm* rMan, graph* g, map* city, im* iMan, cm* cMan);
void printMap(map* city);
int getResIndex(rm* manager, int x, int y);
int getIndIndex(im* manager, int x, int y);
int getComIndex(cm* manager, int x, int y);
void updateMap(queue *q, map* ogCity, map* city, rm* rMan, im* iMan, cm* cMan);
void resolver(graph* g, map* city, rm* rMan, im* iMan, cm* cMan, queue *q);
void getWorkers(int num, rm* manager);

#endif
