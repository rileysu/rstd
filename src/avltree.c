#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arrlist.h"
#include "datatypes.h"
#include "avltree.h"

//NULL pointer as src accepted to init a blank AVLNode
AVLNode initAVLNode(void *src, AVLTree t){
	//Allocate for node header and data as given by nsize in tree
	AVLNode n = malloc(sizeof(struct AVLNode_t) + t->nsize);
	//Callee is required to set parent, height, left, right

	//Only init memory if src != NULL
	if (src != NULL)
		memcpy(dataAVLNode(n), src, t->nsize);

	return n;
}

AVLTree initAVLTree(size_t nsize, int (*compare)(void*,void*)){
	AVLTree t = malloc(sizeof(struct AVLTree_t));

	//Empty tree has no elements or head
	t->head = NULL;
	t->nsize = nsize;
	t->length = 0;
	t->compare = compare;

	return t;
}

void freeAVLNode(AVLNode n){
	free(n);
}

void freeAVLTree(AVLTree t){
	if (t->length != 0){
		//We use a stack because it is lightweight to implement in terms of memory and processing
		//plus it is mathematically better since it can only ever need log(n) space to use while
		//a queue may need n
		
		//Log2(t->length) should work but we make it t->length FOR NOW because i will worry about math
		//libraries later
		
		//Note that the arrlist will work regardless of initial size, it is purely for performance
		ArrList s = initArrList(t->length, sizeof(AVLNode));
	
		//Init the stack with the head of the tree
		addArrList(&(t->head), s);
	
		AVLNode sn;
	
		while (s->clength > 0){
			//Pop from stack and remove element
			sn = *(AVLNode*)getArrList(s->clength-1, s);
			remArrList(s->clength-1, s);
	
			if (sn->left != NULL)
				addArrList(&(sn->left), s);
	
			if (sn->right != NULL)
				addArrList(&(sn->right), s);
	
			freeAVLNode(sn);
		}

		freeArrList(s);
	}

	free(t);
}

AVLNode rotateRightAVLTree(AVLNode n, AVLTree t){
	AVLNode pn = n->parent;
	AVLNode yn = n->left;
	AVLNode t3n = yn->right;

	yn->right = n;
	n->parent = yn;

	n->left = t3n;
	t3n->parent = n;

	if (pn->right == n)
		pn->right = yn;
	else
		pn->left = yn;
	yn->parent = pn;

	n->height = (n->right->height > n->left->height ? n->right->height : n->left->height) + 1;
	yn->height = (yn->right->height > yn->left->height ? yn->right->height : yn->left->height) + 1;
}

AVLNode rotateLeftAVLTree(AVLNode n, AVLTree t){
	
}

AVLNode rotateRightLeftAVLTree(AVLNode n, AVLTree t){
	
}

AVLNode rotateLeftRightAVLTree(AVLNode n, AVLTree t){
	
}

void addAVLTree(void *src, AVLTree t){
	if (t->length == 0){
		t->head = initAVLNode(src, t);
		t->head->parent = NULL;
		t->head->height = 0;
		t->head->left = NULL;
		t->head->right = NULL;
	} else {
		//Add the node
		AVLNode currn = t->head;
	
		for (bool allocated = FALSE; !allocated;){
			if (t->compare(dataAVLNode(currn), src) > 0){ //src > currn
				if (currn->right != NULL){
					printf("%p -> %p\n", currn, currn->right);
					currn = currn->right;
				} else {
					currn->right = initAVLNode(src, t);
					currn->right->parent = currn;
					currn->right->height = 0;
					currn->right->left = NULL;
					currn->right->right = NULL;
					allocated = TRUE;
				}
			} else { // src <= currn
				if (currn->left != NULL){
					printf("%p -> %p\n", currn, currn->left);
					currn = currn->left;
				} else {
					currn->left = initAVLNode(src, t);
					currn->left->parent = currn;
					currn->left->height = 0;
					currn->left->left = NULL;
					currn->left->right = NULL;
					allocated = TRUE;
				}
			}
		}
	}
	
	//TODO
	//Balance tree from currn
	
	
	t->length++;
}

void printDiagsAVLTree(AVLTree t){
	//Performance and size aren't that big of an issue for diags
	ArrList q = initArrList(t->length+1, sizeof(AVLNode));

	//Print generic tree stats
	for (int i = 0; i < 30; i++) printf("-");
	printf("\n");
	
	printf("Tree Head: %p\n", t->head);
	printf("Tree NSize: %lu\n", t->nsize);
	printf("Tree Length: %d\n", t->length);
	printf("Tree Compare: %p\n", t->compare);
	
	if (t->length != 0)
		addArrList(&(t->head), q);

	AVLNode qn;

	while (q->clength > 0){
		//Pop from stack and remove element
		qn = *(AVLNode*)getArrList(0, q);
		remArrList(0, q);

		//Print generic node stats
		for (int i = 0; i < 30; i++) printf("-");
		printf("\n");

		printf("Node Address:%p\n", qn);
		printf("Node Data:");
		for (int i = t->nsize-1; i >= 0; i--){
			printf("%02x",(*(((unsigned char*)dataAVLNode(qn)) + i)));
		}
		printf("\n");	
		printf("Node Parent:%p\n", qn->parent);
		printf("Node Height:%d\n", qn->height);
		printf("Node Left:%p\n", qn->left);
		printf("Node Right:%p\n", qn->right);
	
		for (int i = 0; i < 30; i++) printf("-");
		printf("\n");

		if (qn->left != NULL)
			addArrList(&(qn->left), q);

		if (qn->right != NULL)
			addArrList(&(qn->right), q);
	}
	
	for (int i = 0; i < 30; i++) printf("-");
	printf("\n");

	freeArrList(q);
}
