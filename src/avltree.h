#ifndef AVL_TREE
#define AVL_TREE

#include <stdlib.h>

#define dataAVLNode(N) (((AVLNode) N) + 1) 

typedef int height_t;

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
		//Maybe I should add an enum to simplify output
} *AVLTree;

//Init
AVLNode initAVLNode(void*,AVLTree);
AVLTree initAVLTree(size_t,int(void*,void*));

//Free
void freeAVLNode(AVLNode);
void freeAVLTree(AVLTree);

//Misc

//Simply guarantees the data exists in the tree
void addAVLTree(void*,AVLTree);

//Simply guarantees the data does not exist in the tree
void remAVLTree(void*,AVLTree);

void rebalanceAVLTree(AVLTree);

AVLNode searchAVLTree(void*,AVLTree);

//Diag
void printDiagsAVLTree(AVLTree);
void printDiagsAVLNode(AVLNode, AVLTree);

#endif
