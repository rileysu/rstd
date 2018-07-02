#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dllist.h"

//NULL pointer as src accepted to init a blank DLLNode
DLLNode initDLLNode(void *src, size_t size){
	//Allocate for DLLNode header and data as given by size
	//Allocated memory will look like this for each node:
	//
	// |--------------------|--------------|
	// | Header segment     | Data segment |
	// |------|------|------|--------------|
	// | Size | Next | Prev |     Data     |
	// |------|------|------|--------------|
	//
	//The data segment at src is of size size
	DLLNode n = malloc(sizeof(struct DLLNode_t) + size);

	//Prev and Next not set since the callee is required to handle this
	n->size = size;

	//Only init memory if src != NULL
	if (src != NULL)
		memcpy(dataDLLNode(n),src,size);
	
	return n;	
}

DLList initDLList(){
	DLList l = malloc(sizeof(struct DLList_t));

	//Empty list has no elements or head and tail nodes
	l->head = NULL;
	l->tail = NULL;
	l->length = 0;

	return l;
}

void freeDLLNode(DLLNode n){
	free(n);
}

void freeDLList(DLList l){
	//Iterate through all nodes and deallocate them first
	for (DLLNode n = l->head; n != NULL;){
		DLLNode tn = n;
		//Increment before the free so we do not lose the next node reference
		n = n->next;
		freeDLLNode(tn);
	}
	
	//Then free the rep as no more nodes need to be freed
	free(l);
}

void addDLList(void* src, size_t size, DLList l){
	DLLNode n = initDLLNode(src,size);

	//head == NULL indicates an empty list
	//If empty then new head = n and n has no previous node
	if (l->head == NULL){
		l->head = n;
		n->prev = NULL;
	}
	//Otherwise the previous node for n is the old tail and
	//the next node from the previous node is n
	else{
		n->prev = l->tail;
		l->tail->next = n;
	}
	
	//In both cases the new tail will be n
	//The next node of n will be NULL
	l->tail = n;
	n->next = NULL;

	l->length++;
}

void addAllDLList(DLList sl, DLList dl){
	//Set a static tail node so if sl == dl we do not loop infinitely
	//since addDLList changes the tail node in dl
	DLLNode tailn = sl->tail;

	//If sl is empty then nothing needs to be done
	if (tailn != NULL){
		//Do not interate on tailn since tailn->next may change
		for (DLLNode n = sl->head; n != tailn; n = n->next){
			addDLList(dataDLLNode(n), n->size, dl);
		}

		//Add the tail node we missed in the loop
		addDLList(dataDLLNode(tailn), tailn->size, dl);
	}
}

void delNodeDLList(DLLNode n, DLList l){
	//Change the head if n is the current head
	if (n == l->head)
		l->head = n->next;
	//n != l->head implies n->next != NULL
	else
		n->next->prev = n->prev;
	//Change the tail if n is the current tail
	if (n == l->tail)
		l->tail = n->prev;
	//n != l->tail implies n->prev != NULL
	else
		n->prev->next = n->next;
	
	l->length--;
	freeDLLNode(n);
}

//Undefined behaviour if src is in l
void delDLList(void* src, size_t size, DLList l){
	for (DLLNode n = l->head; n != NULL;){
		//Need to increment inside if statement since increment must be before deletion
		//since after deletion we cannot be sure the node holds the correct reference
		//to the next node
		if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) ){
			DLLNode tn = n;
			n = n->next;
			delNodeDLList(tn, l);
		} else
			n = n->next;
	}
}

void delAllDLList(DLList sl, DLList dl){
	//Free all nodes if sl == dl and reset the rep
	if (sl == dl){
		for (DLLNode n = sl->head; n != NULL;){
			DLLNode tn = n;
			n = n->next;
			freeDLLNode(tn);
		}
		sl->length = 0;
		sl->head = NULL;
		sl->tail = NULL;
	//Iterate through all nodes and remove accordingly otherwise
	} else {
		for (DLLNode n = sl->head; n != NULL; n = n->next){
			delDLList(dataDLLNode(n), n->size, dl);
		}
	}
}

bool containsDLList(void* src, size_t size, DLList l){
	//Iterate through all nodes and return TRUE if equal element found
	for (DLLNode n = l->head; n != NULL; n = n->next){
		if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) )
			return TRUE;
	}

	//No value found therefore element not in list and we return FALSE
	return FALSE;
}

int countDLList(void *src, size_t size, DLList l){
	int count = 0;

	//Iterate through all nodes in the list and increment count accordingly if equal
	for (DLLNode n = l->head; n != NULL; n = n->next){
		if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) ){
			count++;
		}
	}

	//All elements tested and incremented accordingly and thus we return count
	return count;
}

DLLNode getDLList(int ind, DLList l){
	//Find which direction will be more efficient to traverse the linked list
	//Increment from tail if ind is closer to the tail
	if (ind >= l->length/2){
		int i = l->length - 1;
		for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
			//Break and return if found
			if (i == ind){
				return n;
			}
		}
	//Otherwise increment from the head
	} else {
		int i = 0;
		for (DLLNode n = l->head; n != NULL; n = n->next, i++){
			//Break and return if found
			if (i == ind){
				return n;
			}
		}
	}

	//Here so we don't get warnings
	return NULL;
}

void setDLList(int ind, void* src, size_t size, DLList l){
	//Find which direction will be more efficient to traverse the linked list
	//Increment from tail if ind is closer to the tail
	if (ind >= l->length/2){
		int i = l->length - 1;
		for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
			if (i == ind){
				//If sizes are equal then simply copy from src
				if (size == n->size)
					memcpy(dataDLLNode(n), src, size);
				//Otherwise allocate a new node and put it in the old nodes position
				else {
					//Static references before free
					DLLNode nextn = n->next;
					DLLNode prevn = n->prev;
					
					//Free and allocate
					freeDLLNode(n);
					DLLNode newn = initDLLNode(src,size);

					//Corresponding info copied to new node
					newn->next = nextn;
					newn->prev = prevn;

					if (n == l->head)
						l->head = newn;
					//n != l->head implies prevn->prev != NULL
					else
						prevn->prev = newn;
					if (n == l->tail)
						l->tail = newn;
					//n != l->tail implies nextn->next != NULL
					else
						nextn->next = newn;

					return;
				}
			}
		}
	//Otherwise increment from the head
	} else {
		int i = 0;
		for (DLLNode n = l->head; n != NULL; n = n->next, i++){
			if (i == ind){
				if (size == n->size)
                        		memcpy(dataDLLNode(n), src, size);
                                else {
					//Static references before free
                                        DLLNode nextn = n->next;
                                        DLLNode prevn = n->prev;

					//Free and allocate
                                        freeDLLNode(n);
                                        DLLNode newn = initDLLNode(src,size);

					//Corresponding info copied to new node
					newn->next = nextn;
					newn->prev = prevn;

                                        if (n == l->head)
                                                l->head = newn;
                                        //n != l->head implies prevn->prev != NULL
                                        else
                                                prevn->prev = newn;
                                        if (n == l->tail)
                                                l->tail = newn;
                                        //n != l->tail implies nextn->next != NULL
                                        else
                                                nextn->next = newn;

					return;
                                }
			}
		}
	}
}

void squeezeDLList(int ind, void* src, size_t size, DLList l){
	//Find which direction will be more efficient to traverse the linked list
	//Increment from tail if ind is closer to the tail
        if (ind >= l->length/2){
                int i = l->length - 1;
                for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
                        if (i == ind){
				//Alloc
				DLLNode newn = initDLLNode(src,size);
				
				//Init new node
				newn->next = n;
				newn->prev = n->prev;

				if (n->prev != NULL)
					n->prev->next = newn;
				//n->prev != NULL implies n is the head
				else
					l->head = newn;
				n->prev = newn;

				l->length++;
				return;
                        }
                }
	//Otherwise increment from the head
        } else {
                int i = 0;
                for (DLLNode n = l->head; n != NULL; n = n->next, i++){
                        if (i == ind){
				//Alloc	
				DLLNode newn = initDLLNode(src,size);
				
				//Init new node
				newn->next = n;
				newn->prev = n->prev;

				if (n->prev != NULL)
					n->prev->next = newn;
				//n->prev == NULL implies n is the head
				else
					l->head = newn;
				n->prev = newn;

				l->length++;
				return;
                        }
                }
	}                                                                   
}

void remDLList(int ind, DLList l){
	//Find which direction will be more efficient to traverse the linked list
	//Increment from tail if ind is closer to the tail
        if (ind >= l->length/2){
                int i = l->length - 1;
                for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
                        if (i == ind){
				//We do not care about the sanity of the loop since we return
				delNodeDLList(n, l);
				return;
                        }
                }
	//Otherwise increment from the head
        } else {
                int i = 0;
                for (DLLNode n = l->head; n != NULL; n = n->next, i++){
                        if (i == ind){
				//We do not care about the sanity of the loop since we return
				delNodeDLList(n, l);
                                return;
                        }
                }
        }
}

void printDiagsDLList(DLList l){
        for (int i = 0; i < 30; i++)
		printf("-");
        printf("\n");

        printf("List Length:%d\n", l->length);

        printf("Forwards:\n");
        for (DLLNode n = l->head; n != NULL; n = n->next){
		for (int j = n->size-1; j >= 0; j--){
                        printf("%02x",(*(((unsigned char*)dataDLLNode(n)) + j)));
                }
                printf("\n");
        }

        printf("Backwards:\n");
        for (DLLNode n = l->tail; n != NULL; n = n->prev){
                for (int j = n->size-1; j >= 0; j--){
                        printf("%02x",(*(((unsigned char*)dataDLLNode(n)) + j)));
                }
                printf("\n");
        }

        for (int i = 0; i < 30; i++)
		printf("-");
        printf("\n");
}
