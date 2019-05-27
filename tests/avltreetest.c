#include <stdio.h>
#include <string.h>

#include "avltree.h"
#include "datatypes.h"

int compareInt(void *src1, void *src2){
	if (*(int*)src1 > *(int*)src2)
		return 1;
	else if (*(int*)src1 < *(int*)src2)
		return -1;
	else
		return 0;
}

bool testInitAndFree(){
	int a = 4;
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	a = 2;
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	a = 6;
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	a = 1;
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	a = 3;
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	a = 5;
	printDiagsAVLTree(t);
	addAVLTree(&a, t);
	printDiagsAVLTree(t);
	freeAVLTree(t);
	return TRUE;
}

int main(void){
	printf("Test AVLTree\n");
	printf("Init and Free: %d\n", testInitAndFree());

	return 0;
}
