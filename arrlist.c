#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arrlist.h"

ArrList initArrList(int length, size_t nsize){
	struct ArrList_t *l = malloc(sizeof(struct ArrList_t));

	if ((l->head = malloc(nsize*length)) == NULL) 
		fprintf(stderr, "Malloc failed in initArrList.\n");
	l->nsize = nsize;
	l->clength = 0;
	l->length = length;

	return l;
}

void freeArrList(ArrList l){
	free(l->head);
	free(l);
}

void expandArrList(int size, ArrList l){
	void *nhead = realloc(l->head,size*l->nsize);
	if (nhead == NULL){
		fprintf(stderr, "Realloc failed in expandArrList.\n");
		exit(-1);
	} else {
		l->head = nhead;
		l->length = size;
	}
}

void addArrList(void *src,  ArrList l){
	if (l->clength < l->length){
		memcpy((char*)l->head + l->clength*l->nsize,src,l->nsize);
		l->clength++;
	} else {
		expandArrList(l->length*2,l);
		memcpy((char*)l->head + l->clength*l->nsize,src,l->nsize);
		l->clength++;
	}

}

void addAllArrList(ArrList sl, ArrList dl){
	if (sl == dl)
		expandArrList(sl->length*2,sl);
	int clength = sl->clength;
	for (int i = 0; i < clength; i++){
		addArrList((char*)sl->head + i*dl->nsize,dl);
	}
}

void delArrList(void *src, ArrList l){
	for (int i = 0; i < l->length; i++){
		if ( (memcmp(src,((char*)l->head + i*l->nsize),l->nsize) == 0) ){
			remArrList(i,l);
			i--;
		}
	}
}

void delAllArrList(ArrList sl, ArrList dl){
	if (sl == dl){
		for (int i = dl->clength - 1; i >= 0; i--){
			remArrList(i,dl);
		}
	} else {
		for (int i = 0; i < sl->clength; i++){
			delArrList((char*)sl->head + i*dl->nsize,dl);
		}
	}
}

bool containsArrList(void *src, ArrList l){
	for (int i = 0; i < l->clength; i++){
		if (memcmp(src,l->head + i*l->nsize,l->nsize) == 0){
			return TRUE;
		}
	}
	return FALSE;
}

int countArrList(void *src, ArrList l){
	int count = 0;
	for (int i = 0; i < l->clength; i++){
		if (memcmp(src,(char*)l->head + i*l->nsize,l->nsize)) count++;
	}
	return count;
}

void *getArrList(int ind, ArrList l){
	return (char*)l->head + ind*l->nsize;
}

void setArrList(int ind, void *src, ArrList l){
	memcpy((char*)l->head + ind*l->nsize, src, l->nsize);
}

void squeezeArrList(int ind, void* src, ArrList l){
	l->clength++;
	if (l->clength > l->length)
		expandArrList(l->length*2,l);
	for (int j = l->clength - 2; j >= ind; j--)
		memcpy((char*)l->head + (j+1)*l->nsize, (char*)l->head + j*l->nsize, l->nsize);
	setArrList(ind,src,l);
}

void remArrList(int ind, ArrList l){
	memcpy((char*)l->head + ind*l->nsize, (char*)l->head + (ind+1)*l->nsize, (l->clength - ind)*l->nsize);
	l->clength--;
}

void *getHeadArrList(ArrList l){
	return l->head;
}

void *getTailArrList(ArrList l){
	return (char*)l->head + (l->clength-1) * l->nsize;
}

void printDiagsArrList(ArrList l){	
	for (int i = 0; i < 30; i++) printf("-");
	printf("\n");
	
	printf("List Length:%d\n",l->length);
	printf("List CLength:%d\n",l->clength);

	printf("Contains:\n");
	for (int i = 0; i < l->clength; i++){
		for (int j = l->nsize-1; j >= 0; j--){
			printf("%02x",(*(((unsigned char*)l->head) + i*l->nsize + j)));
		}
		printf("\n");
	}

	for (int i = 0; i < 30; i++) printf("-");
	printf("\n");
}
