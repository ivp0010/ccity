#ifndef FUNC_H
#define FUNC_H
#include <stdlib.h>
#include <stdio.h>
#include "cell.h"

void addRes(rm* manager);
void addInd(im* manager);
void addCom(cm* manager);
void splitter(map* city, char filename[], rm* rman, im* iman, cm* cman);

#endif
