#ifndef ARRLIST_H
#define ARRLIST_H

#include <stdlib.h>

#include "datatypes.h"

#define forArrList(AP, BP) for( void *AP = BP->head; AP < (void*)((char*)(BP->head) + BP->clength * BP->nsize); AP = (void*)((char*)AP + BP->nsize) )

typedef struct ArrList_t{
	void *head;
	size_t nsize;
	int clength;
	int length;
} *ArrList;

//Init
ArrList initArrList(int length, size_t nsize); //C

//Free
void freeArrList(ArrList); //C

//Misc
void expandArrList(int,ArrList);

void addArrList(void*,ArrList); //C
void addAllArrList(ArrList,ArrList); //C

void delArrList(void*,ArrList); //C
void delAllArrList(ArrList,ArrList); //C

bool containsArrList(void*,ArrList);//C
int countArrList(void*,ArrList); //C

void *getArrList(int,ArrList);//C
void setArrList(int,void*,ArrList);
void squeezeArrList(int,void*,ArrList);
void remArrList(int,ArrList);

void *getHeadArrList(ArrList);//C
void *getTailArrList(ArrList);//C

//Diag
void printDiagsArrList(ArrList);//C

#endif
