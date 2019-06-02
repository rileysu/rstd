#ifndef HTABLE_H
#define HTABLE_H

#include <stdlib.h>
#include <stdint.h>

#include "arrlist.h"
#include "datatypes.h"
#include "derefvoid.h"

#define getPopulatedHTable(AP, HP) derefVoid(AP, bool)
#define getKeyHTable(AP, HP) ((void*)((char*)AP + sizeof(bool)))
#define getValueHTable(AP, HP) ((void*)((char*)AP + sizeof(bool) + HP->keysize))

typedef struct HTable_t{
	ArrList l;
	size_t keysize;
	size_t valuesize;
	int length;
	int clength;
	unsigned int (*hash)(void*, size_t, int);
} *HTable;

//Init
HTable initHTable(int,size_t,size_t,unsigned int(void*,size_t,int));

//Free
void freeHTable(HTable);

//Misc
void expandHTable(int,HTable);

void setHTable(void*,void*,HTable);

void *getHTable(void*,HTable);

void delHTable(void*,HTable);

//Diag
void printDiagsHTable(HTable);

#endif
