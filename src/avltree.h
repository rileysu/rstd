#ifndef AVL_TREE
#define AVL_TREE

#include <stdlib.h>

#include "datatypes.h"

#define dataAVLNode(N) (((AVLNode) N) + 1) 

typedef unsigned int height_t;

typedef struct AVLNode_t{
	struct AVLNode_t *parent;
	height_t height;
	struct AVLNode_t *left;
	struct AVLNode_t *right;
} *AVLNode;

typedef struct AVLTree_t{
	AVLNode head;
	size_t nsize;
	int length;
	int (*compare)(void*,void*); 
		//: {-1, 0, 1}
		//-1 ==> src1 < src2
		//0 ==> src1 == src2
		//1 ==> src1 > src2
		//All functions use this for internal comparison
} *AVLTree;

//Init
AVLNode initAVLNode(void*,AVLTree);
AVLTree initAVLTree(size_t,int(void*,void*));

//Free
void freeAVLNode(AVLNode);
void freeAVLTree(AVLTree);

//Misc

//Return whether the data exists in the tree
bool containsAVLTree(void*,AVLTree);

//Guarantees the data exists in the tree
void addAVLTree(void*,AVLTree);

//Return the data from the node that matches src
void *getAVLTree(void*,AVLTree);

//Guarantees the data does not exist in the tree
void delAVLTree(void*,AVLTree);

//Diag
void printDiagsAVLTree(AVLTree);
void printDiagsAVLNode(AVLNode, AVLTree);

#endif
