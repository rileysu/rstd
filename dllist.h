#ifndef DLLIST_H
#define DLLIST_H

#include <stdlib.h>

#include "datatypes.h"

typedef struct DLLNode_t{
	size_t size;
	struct DLLNode_t *next;
	struct DLLNode_t *prev;
} *DLLNode;

typedef struct DLList_t{
	DLLNode head;
	DLLNode tail;
	int length;
} *DLList;

//Init
DLLNode initDLLNode(void*,size_t); 
DLList initDLList(); 

//Free
void freeDLLNode(DLLNode); 
void freeDLList(DLList); 

//Misc
void addDLList(void*,size_t,DLList); 
void addAllDLList(DLList,DLList); 

void delDLList(void*,size_t,DLList); 
void delAllDLList(DLList,DLList); 

bool containsDLList(void*,size_t,DLList);
int countDLList(void*,size_t,DLList); 

DLLNode getDLList(int,DLList);
void setDLList(int,void*,size_t,DLList); 
void squeezeDLList(int,void*,size_t,DLList);
void remDLList(int,DLList);

DLLNode getHeadDLList(DLList);
DLLNode getTailDLList(DLList);

//Diag
void printDiagsDLList(DLList);

#endif
