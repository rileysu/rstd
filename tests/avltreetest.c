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

typedef struct IntStr_t{
	int key;
	char val[12];
} IntStr;

int compareMap(void *src1, void *src2){
	IntStr *is1 = (IntStr*)src1;
	IntStr *is2 = (IntStr*)src2;

	if (is1->key > is2->key)
		return 1;
	else if (is1->key < is2->key)
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

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 1 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 0 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 0)
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

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 1 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 0 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 0)
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

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 1 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 0 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 0)
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

	if (*(int*)dataAVLNode(t->head) != 2 || t->head->height != 1 ||
			*(int*)dataAVLNode(t->head->left) != 1 || t->head->left->height != 0 ||
			*(int*)dataAVLNode(t->head->right) != 3 || t->head->right->height != 0)
		test = FALSE;

	freeAVLTree(t);
	return test;
}

bool testMapExample(){
	AVLTree t = initAVLTree(sizeof(struct IntStr_t), compareMap);
	bool test = TRUE;
	IntStr a;
	
	a.key = 0;
	strcpy(a.val, "riley is cl");

	addAVLTree(&a, t);

	a.key = 1;
	strcpy(a.val, "riley nt cl");

	addAVLTree(&a, t);

	a.key = 2;
	strcpy(a.val, "riley mb cl");

	addAVLTree(&a, t);

	int b;
	IntStr *c;

	c = (IntStr*)dataAVLNode(t->head);
	if (c->key != 1)
		test = FALSE;

	c = (IntStr*)dataAVLNode(t->head->left);
	if (c->key != 0)
		test = FALSE;

	c = (IntStr*)dataAVLNode(t->head->right);
	if (c->key != 2)
		test = FALSE;

	b = 0;
	c = getAVLTree(&b, t);
	if (strcmp(c->val, "riley is cl") != 0)
		test = FALSE;

	b = 1;
	c = getAVLTree(&b, t);
	if (strcmp(c->val, "riley nt cl") != 0)
		test = FALSE;

	b = 2;
	c = getAVLTree(&b, t);
	if (strcmp(c->val, "riley mb cl") != 0)
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
	printf("Map Example: %d\n", testMapExample());

	return 0;
}
