#ifndef HTABLE_H
#define HTABLE_H

#include <stdlib.h>
#include <stdint.h>

#include "dllist.h"

#define keyHTNode(N) (((HTNode)N)+1)
#define valueHTNode(N) ((char*)(((HTNode)N) + 1) + N->keysize)

typedef struct HTNode_t{
	size_t keysize;
	size_t valuesize;
} *HTNode;

typedef struct HTable_t{
	DLList *arr;
	int clength;
	int length;
	unsigned int (*hash)(void*, size_t, int);
} *HTable;

//Init
HTNode initHTNode(void*,size_t,void*,size_t,DLList);
HTable initHTable(int,unsigned int(void*,size_t,int));

//Free
void freeHTNode(HTNode,DLList);
void freeHTable(HTable);

//Misc
void addHTable(void*,size_t,void*,size_t,HTable);

HTNode getHTable(void*,size_t,HTable);

void remHTable(void*,size_t,HTable);

//Diag
void printDiagsHTable(HTable);

#endif
