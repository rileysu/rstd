#ifndef ARRLIST_H
#define ARRLIST_H

#include <stdlib.h>

#include "datatypes.h"

#define forArrList(AP, BP) for(void *AP = BP->head; AP < (void*)((char*)(BP->head) + BP->clength * BP->nsize); AP = (void*)((char*)AP + BP->nsize) )

typedef struct ArrList_t{
	void *head;
	size_t nsize;
	int clength;
	int length;
} *ArrList;

//Init
ArrList initArrList(int, size_t);

//Free
void freeArrList(ArrList);

//Misc
void expandArrList(int,ArrList);

void addArrList(void*,ArrList);
void addAllArrList(ArrList,ArrList);

void delArrList(void*,ArrList);
void delAllArrList(ArrList,ArrList);

bool containsArrList(void*,ArrList);
int countArrList(void*,ArrList);

void *getArrList(int,ArrList);
void setArrList(int,void*,ArrList);
void squeezeArrList(int,void*,ArrList);
void remArrList(int,ArrList);

void *getHeadArrList(ArrList);
void *getTailArrList(ArrList);

//Diag
void printDiagsArrList(ArrList);

#endif
