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
		//plus it needs less space than a queue since it can only ever need log(n) space to use while
		//a queue may need n because we can use a depth first search to free all nodes with a stack
		
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
	
			if (sn->left != NULL) //Push to stack
				addArrList(&(sn->left), s);
	
			if (sn->right != NULL) //Push to stack
				addArrList(&(sn->right), s);
	
			freeAVLNode(sn);
		}

		freeArrList(s);
	}

	free(t);
}

AVLNode rotateRightAVLTree(AVLNode n, AVLTree t){
	//Left child of n becomes new root respective to n
	//Right child of new root becomes left child of old root
	
	AVLNode ln = n->left;
	AVLNode lnrc = ln->right;

	ln->right = n;
	n->left = lnrc;

	//Parent of n is now the old left node of n
	//Parent of the old left node is now the parent of n (Hence new root)
	
	ln->parent = n->parent;
	n->parent  = ln;

	if (ln->parent != NULL){
		if (ln->parent->right == n){
			ln->parent->right = ln;
		} else {
			ln->parent->left = ln;
		}
	}
}

AVLNode rotateLeftAVLTree(AVLNode n, AVLTree t){
	//Right child of n becomes new root respective to n
	//Left child of new root becomes right child of old root

	AVLNode rn = n->right;
	AVLNode rnlc = rn->left;

	rn->left = n;
	n->right = rnlc;

	//Parent of n is now the old right node of n
	//Parent of the old right node is now the parent of n (Hence new root)
	
	rn->parent = n->parent;
	n->parent = rn;

	//Fix parent not refering to the new root (if it exists)
	if (rn->parent != NULL){
		if (rn->parent->right == n){
			rn->parent->right = rn;
		} else {
			rn->parent->left = rn;
		}
	}
	

}

AVLNode rotateLeftRightAVLTree(AVLNode n, AVLTree t){
	
}

AVLNode rotateRightLeftAVLTree(AVLNode n, AVLTree t){
	
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

		bool allocated = FALSE;
		while (!allocated){
			if (t->compare(dataAVLNode(currn), src) < 0){ //src > currn
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

void delAVLTree(void *src, AVLTree t){
	AVLNode currn = t->head;

	bool deleted = FALSE;
	while (!deleted){
		int comp = t->compare(dataAVLNode(currn), src);
		if (comp == 0){ //src == currn
			if (currn->right == NULL && currn->left == NULL){ //Case No children present
				//Simply delete the node since nothing depends on it
				
				//Remove the reference from the parent to the child if the parent exists
				if (currn->parent != NULL){
					if (currn->parent->right == currn){
						currn->parent->right = NULL;
					} else {
						currn->parent->left = NULL;
					}
				}

				//Change the head to null if currn is the only node
				if (t->head == currn){
					t->head = NULL;
				}

				//Free the node using the correct free function
				freeAVLNode(currn);
			} else if (currn->right == NULL){ //Case left child present
				//Simply replace the current node with its single child
			
				//Change parent to refer to the child of currn
				if (currn->parent != NULL){
					if (currn->parent->right == currn){
						currn->parent->right = currn->left;
					} else {
						currn->parent->left = currn->left;
					}
				}

				//Change the head to the new node if currn is the head
				if (t->head == currn){
					t->head = currn->left;
				}
				
				//Change the parent of the new currn to 
				currn->left->parent = currn->parent;

				//Free the node using the correct free function
				freeAVLNode(currn);
			} else if (currn->left == NULL){ //Case right child present
				//Simply replace the current node with its single child
			
				//Change parent to refer to the child of currn
				if (currn->parent != NULL){
					if (currn->parent->right == currn){
						currn->parent->right = currn->right;
					} else {
						currn->parent->left = currn->right;
					}
				}

				//Change the head to the new node if currn is the head
				if (t->head == currn){
					t->head = currn->right;
				}
				
				//Change the parent of the new currn to 
				currn->right->parent = currn->parent;

				//Free the node using the correct free function
				freeAVLNode(currn);
			} else { //Case both children present
			
				//Remove the node from the heighest subtree
				//Find either the greatest node in the min tree
				//or the min node in the max tree
				//Both are a guaranteed replacement for the currn
				if (currn->left->height > currn->right->height){
					//Find max node in min tree
					//Guaranteed to be greatert
					AVLNode maxn;
					for (maxn = currn->left; maxn->right != NULL; maxn = maxn->right);
					
					//Replace the currn with maxn

				} else {
				
				}
			}
			
			//Decrement the length of the tree
			t->length--;
		} else if (comp < 0) { //src > currn
			if (currn->right != NULL){
				
			} else {

			}
		} else { //src <= currn
			
		}
	}
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
		//Pop from queue and remove element
		qn = *(AVLNode*)getArrList(0, q);
		remArrList(0, q);

		printDiagsAVLNode(qn, t);

		if (qn->left != NULL)
			addArrList(&(qn->left), q);

		if (qn->right != NULL)
			addArrList(&(qn->right), q);
	}
	
	for (int i = 0; i < 30; i++) printf("-");
	printf("\n");

	freeArrList(q);
}

void printDiagsAVLNode(AVLNode n, AVLTree t){
		for (int i = 0; i < 30; i++) printf("-");
		printf("\n");

		printf("Node Address:%p\n", n);
		
		//Print hex of whatever the node contains
		printf("Node Data: 0x");
		for (int i = t->nsize-1; i >= 0; i--){
			printf("%02x",(*(((unsigned char*)dataAVLNode(n)) + i)));
		}

		printf("\n");	
		printf("Node Parent:%p\n", n->parent);
		printf("Node Height:%d\n", n->height);
		printf("Node Left:%p\n", n->left);
		printf("Node Right:%p\n", n->right);
	
		for (int i = 0; i < 30; i++) printf("-");
		printf("\n");


}
