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
	bool test = TRUE;

	if (t->nsize != sizeof(int) || t->length != 0 || t->head != NULL)
		test = FALSE;

	freeAVLTree(t);
	return test;
}

bool testDefinedBehaviour(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	bool test = TRUE;
	int a = 0;

	//Remove from empty list
	delAVLTree(&a, t);
	
	if (t->nsize != sizeof(int) || t->length != 0 || t->head != NULL)
		test = FALSE;

	//Add element twice
	addAVLTree(&a, t);	
	addAVLTree(&a, t);
		
	if (t->nsize != sizeof(int) || t->length != 1 || !containsAVLTree(&a, t))
		test = FALSE;

	//Remove element not present
	a++;
	delAVLTree(&a, t);
	a--;

	if (t->nsize != sizeof(int) || t->length != 1 || !containsAVLTree(&a, t))
		test = FALSE;
	
	freeAVLTree(t);
	return test;
}

bool testMassAddAndRemove(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	bool test = TRUE;
	
	for (int i = 0; i < 25; i++){
		srand(SEED + i);

		for (int i = 0; i < 10000; i++){
			int in = rand();
			addAVLTree(&in, t);  
		}
	
		if (t->length <= 0 || t->length > 10000)
			test = FALSE;
	
		srand(SEED + i);
	
		for (int i = 0; i < 10000; i++){
			int in = rand();
			if (!containsAVLTree(&in, t)){
				test = FALSE;
			}
			delAVLTree(&in, t);
			if (containsAVLTree(&in, t)){
				test = FALSE;
			}
		}
		
		if (t->length != 0)
			test = FALSE;
	}

	freeAVLTree(t);
	return test;
}

bool testCorrectRotations(){
	AVLTree t = initAVLTree(sizeof(int), compareInt);
	bool test = TRUE;
	int a;

	//Left rotation
	a = 1;
	addAVLTree(&a, t);
	a = 2;
	addAVLTree(&a, t);
	a = 3;
	addAVLTree(&a, t);

	if (t->nsize != sizeof(int) || t->length != 3)
		test = FALSE;

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 2 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 1 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 1)
		test = FALSE;
	
	freeAVLTree(t);
	t = initAVLTree(sizeof(int), compareInt);

	//Right rotation
	a = 3;
	addAVLTree(&a, t);
	a = 2;
	addAVLTree(&a, t);
	a = 1;
	addAVLTree(&a, t);

	if (t->nsize != sizeof(int) || t->length != 3)
		test = FALSE;

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 2 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 1 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 1)
		test = FALSE;

	freeAVLTree(t);
	t = initAVLTree(sizeof(int), compareInt);

	
	//Right Left rotation
	a = 1;
	addAVLTree(&a, t);
	a = 3;
	addAVLTree(&a, t);
	a = 2;
	addAVLTree(&a, t);

	if (t->nsize != sizeof(int) || t->length != 3)
		test = FALSE;

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 2 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 1 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 1)
		test = FALSE;
	
	freeAVLTree(t);
	t = initAVLTree(sizeof(int), compareInt);

	//Left Right rotation
	a = 3;
	addAVLTree(&a, t);
	a = 1;
	addAVLTree(&a, t);
	a = 2;
	addAVLTree(&a, t);

	if (t->nsize != sizeof(int) || t->length != 3)
		test = FALSE;

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 2 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 1 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 1)
		test = FALSE;

	freeAVLTree(t);
	return test;
}

int main(void){
	printf("Test AVLTree\n");
	printf("Init and Free: %d\n", testInitAndFree());
	printf("Defined Behaviour: %d\n", testDefinedBehaviour());
	printf("Mass Add and Remove: %d\n", testMassAddAndRemove());
	printf("Correct Rotations: %d\n", testCorrectRotations());

	return 0;
}
