#include <stdio.h>
#include <string.h>

#include "avltree.h"
#include "datatypes.h"

#define SEED 35

int compareInt(void *src1, void *src2){
	if (*(int*)src1 > *(int*)src2)
		return 1;
	else if (*(int*)src1 < *(int*)src2)
		return -1;
	else
		return 0;
}

bool testInitAndFree(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	freeAVLTree(t);
	return TRUE;
}

bool testMassAddAndRemove(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	
	bool out = TRUE;
	
	srand(SEED);

	for (int i = 0; i < 1000000; i++){
		int in = rand();
		addAVLTree(&in, t);  
	}

	if (out == TRUE && t->length > 0)
		out = TRUE;

	srand(SEED);

	for (int i = 0; i < 1000000; i++){
		int in = rand();
		remAVLTree(&in, t);  
	}
	
	if (out == TRUE && t->length == 0)
		out = TRUE;

	freeAVLTree(t);
	return out;
}

bool testCorrectAddAndRemove(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);

	int a = 5;
	addAVLTree(&a, t);
	a = 3;
	addAVLTree(&a, t);
	a = 7;
	addAVLTree(&a, t);
	a = 2;
	addAVLTree(&a, t);
	a = 4;
	addAVLTree(&a, t);
	a = 6;
	addAVLTree(&a, t);
	a = 8;
	addAVLTree(&a, t);

	//a = 6;
	//remAVLTree(&a, t);

	//a = 5;
	//remAVLTree(&a, t);

	//a = 7;
	//remAVLTree(&a, t);

	printDiagsAVLTree(t);

	freeAVLTree(t);
	return TRUE;
}

int main(void){
	printf("Test AVLTree\n");
	printf("Init and Free: %d\n", testInitAndFree());
	printf("Mass Add and Remove: %d\n", testMassAddAndRemove());
	printf("Correct Add and Remove: %d\n", testCorrectAddAndRemove());

	return 0;
}
