#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arrlist.h"

ArrList initArrList(int length, size_t nsize){
	struct ArrList_t *l = malloc(sizeof(struct ArrList_t)); 

	//Return NULL and print error  to indicate no memory allocated
	if ((l->head = malloc(nsize*length)) == NULL){ 
		fprintf(stderr, "Malloc failed in initArrList.\n");
		return NULL;
	}

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
	
	//Exit after realloc failure as list requires new element when expanded
	if (nhead == NULL){
		fprintf(stderr, "Realloc failed in expandArrList.\n");
		exit(-1);
	} else {
		l->head = nhead;
		l->length = size;
	}
}

//NULL pointer means to allocate an empty node
void addArrList(void *src,  ArrList l){
	//Check if ArrList needs to be resized
	if (l->clength == l->length)
		expandArrList(l->length*2,l);

	if (src != NULL)
		memcpy((char*)l->head + l->clength*l->nsize,src,l->nsize);

	l->clength++;

}

void addAllArrList(ArrList sl, ArrList dl){
	//If sl == dl then the next loop will not end since the add function increments clength by 1
	//So we create a static clength
	int clength = sl->clength;

	//Iterate through all elements in sl and add accordingly
	for (int i = 0; i < clength; i++){
		addArrList((char*)sl->head + i*dl->nsize,dl);
	}
}

//Undefined behaviour if src is in l
void delArrList(void *src, ArrList l){
	//Iterate through all indicies and delete those that match
	for (int i = 0; i < l->length; i++){
		if ( (memcmp(src,((char*)l->head + i*l->nsize),l->nsize) == 0) ){
			remArrList(i,l);
			//Iterate i down since now the i'th element will be different
			i--;
		}
	}
}

void delAllArrList(ArrList sl, ArrList dl){
	//Protect function from failing due to deleting all elements in the same list
	if (sl == dl)
		//Simply reset the ArrList by setting clength to 0
		dl->clength = 0;
	else {
		for (int i = 0; i < sl->clength; i++){
			delArrList((char*)sl->head + i*dl->nsize,dl);
		}
	}
}

bool containsArrList(void *src, ArrList l){
	//Iterate through all indicies and return TRUE if equal element found
	for (int i = 0; i < l->clength; i++){
		if (memcmp(src,l->head + i*l->nsize,l->nsize) == 0){
			return TRUE;
		}
	}

	//No element in the list is equal and thus we return FALSE
	return FALSE;
}

int countArrList(void *src, ArrList l){
	int count = 0;

	//Iterate through all elements in arrlist and increment count accordingly if equal
	for (int i = 0; i < l->clength; i++){
		if (memcmp(src,(char*)l->head + i*l->nsize,l->nsize)) count++;
	}

	//All elements tested and incremented accordingly and thus we return the count
	return count;
}

void *getArrList(int ind, ArrList l){
	//Simply increment the head pointer by the size * ind to find the pointer to the data
	return (char*)l->head + ind*l->nsize;
}

void setArrList(int ind, void *src, ArrList l){
	//Simply copy the new data from src to the corresponding pointer to the data in the ArrList
	memcpy(getArrList(ind, l), src, l->nsize);
}

//Can only squeeze between elements and at 0, not at clength
void squeezeArrList(int ind, void* src, ArrList l){
	//Increment clength so we know whether to expand or not
	l->clength++;

	//Expand if required
	if (l->clength > l->length)
		expandArrList(l->length*2,l);

	//memcpy doesn't support overlapping memory so we need to do this		
	for (int j = l->clength - 2; j >= ind; j--)
		if (src != NULL)
			memcpy((char*)l->head + (j+1)*l->nsize, (char*)l->head + j*l->nsize, l->nsize);
	
	//Empty element at ind now set
	setArrList(ind,src,l);
}

void remArrList(int ind, ArrList l){
	//Memory is moved down so this will work regardless of memcpy implementation
	memcpy((char*)l->head + ind*l->nsize, (char*)l->head + (ind+1)*l->nsize, (l->clength - ind)*l->nsize);
	l->clength--;
}

void *getHeadArrList(ArrList l){
	return l->head;
}

void *getTailArrList(ArrList l){
	//Jump to the end element pointer using clength and size
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
