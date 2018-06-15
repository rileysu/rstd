#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dllist.h"

#define dataDLLNode(N) (N+1) 

DLLNode initDLLNode(void *src, size_t size){
	DLLNode n = malloc(sizeof(struct DLLNode_t) + size);

	n->size = size;

	memcpy(dataDLLNode(n),src,size);
	
	return n;	
}

DLList initDLList(){
	DLList l = malloc(sizeof(struct DLList_t));

	l->head = NULL;
	l->tail = NULL;
	l->length = 0;

	return l;
}

void freeDLLNode(DLLNode n){
	free(n);
}

void freeDLList(DLList l){
	for (DLLNode n = l->head; n != NULL;){
		DLLNode tn = n;
		n = n->next;
		freeDLLNode(tn);
	}
	free(l);
}

void addDLList(void* src, size_t size, DLList l){
	DLLNode n = initDLLNode(src,size);

	if (l->head == NULL){
		l->head = n;
		n->prev = NULL;
	}
	else{
		n->prev = l->tail;
		l->tail->next = n;
	}
	
	l->tail = n;
	n->next = NULL;
	l->length++;
}

void addAllDLList(DLList sl, DLList dl){
	DLLNode tailn = sl->tail;
	for (DLLNode n = sl->head; n != tailn; n = n->next){
		addDLList(dataDLLNode(n), n->size, dl);
	}
	addDLList(dataDLLNode(tailn), tailn->size, dl);
}

void delDLList(void* src, size_t size, DLList l){
	for (DLLNode n = l->head; n != NULL;){
		if ( src == dataDLLNode(n) ){
			fprintf(stderr,"Cannot use element is list as reference to delete.\n");
		} else if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) ){
			if (n->next != NULL) 
				n->next->prev = n->prev;
			if (n->prev != NULL)
				n->prev->next = n->next;
			if (n == l->head)
				l->head = n->next;
			if (n == l->tail)
				l->tail = n->prev;
			l->length--;
			
			DLLNode tn = n;
			n = n->next;
			freeDLLNode(tn);
		} else {
			n = n->next;
		}
	}
}

void delAllDLList(DLList sl, DLList dl){
	if (sl == dl){
		for (DLLNode n = sl->head; n != NULL;){
			DLLNode tn = n;
			n = n->next;
			freeDLLNode(tn);
		}
		sl->length = 0;
		sl->head = NULL;
		sl->tail = NULL;
	} else {
		for (DLLNode n = sl->head; n != NULL; n = n->next){
			delDLList(dataDLLNode(n), n->size, dl);
		}
	}
}

bool containsDLList(void* src, size_t size, DLList l){
	for (DLLNode n = l->head; n != NULL; n = n->next){
		if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) ){
			return TRUE;
		}
	}
	return FALSE;
}

int countDLList(void *src, size_t size, DLList l){
	int count = 0;
	for (DLLNode n = l->head; n != NULL; n = n->next){
		if ( (size == n->size) && (memcmp(src, dataDLLNode(n), n->size) == 0) ){
			count++;
		}
	}
	return count;
}

DLLNode getDLList(int ind, DLList l){
	if (ind >= l->length || ind < 0){
		fprintf(stderr, "Invalid index specified in get.\n");
	} else if (ind >= l->length/2){
		int i = l->length - 1;
		for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
			if (i == ind){
				return n;
			}
		}
	} else {
		int i = 0;
		for (DLLNode n = l->head; n != NULL; n = n->next, i++){
			if (i == ind){
				return n;
			}
		}
	}
}

void setDLList(int ind, void* src, size_t size, DLList l){
	if (ind >= l->length || ind < 0){
		fprintf(stderr, "Invalid index specified in set.\n");
	} else if (ind >= l->length/2){
		int i = l->length - 1;
		for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
			if (i == ind){
				if (size == n->size){
					memcpy(dataDLLNode(n), src, size);
				} else {
					DLLNode nextn = n->next;
					DLLNode prevn = n->prev;
					
					freeDLLNode(n);
					DLLNode newn = initDLLNode(src,size);

					newn->next = nextn;
					newn->prev = prevn;

					if (nextn != NULL)
						nextn->prev = newn;
					if (prevn != NULL)
						prevn->next = newn;
					if (n == l->head)
						l->head = newn;
					if (n == l->tail)
						l->tail = newn;

					return;
				}
			}
		}
	} else {
		int i = 0;
		for (DLLNode n = l->head; n != NULL; n = n->next, i++){
			if (i == ind){
                                if (size == n->size){
                                        memcpy(dataDLLNode(n), src, size);
                                } else {
                                        DLLNode nextn = n->next;
                                        DLLNode prevn = n->prev;

                                        freeDLLNode(n);
                                        DLLNode newn = initDLLNode(src,size);

					newn->next = nextn;
					newn->prev = prevn;

                                        if (nextn != NULL)
                                                nextn->prev = newn;
                                        if (prevn != NULL)
                                                prevn->next = newn;
                                        if (n == l->head)
                                                l->head = newn;
                                        if (n == l->tail)
                                                l->tail = newn;

                                        return;
                                }

			}
		}
	}
}

void squeezeDLList(int ind, void* src, size_t size, DLList l){
        if (ind >= l->length || ind < 0){
                fprintf(stderr, "Invalid index specified in set.\n");
        } else if (ind >= l->length/2){
                int i = l->length - 1;
                for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
                        if (i == ind){
				DLLNode newn = initDLLNode(src,size);
				
				newn->next = n;
				newn->prev = n->prev;

				if (n->prev != NULL)
					n->prev->next = newn;
				else
					l->head = newn;
				n->prev = newn;

				l->length++;
				return;
                        }
                }
        } else {
                int i = 0;
                for (DLLNode n = l->head; n != NULL; n = n->next, i++){
                        if (i == ind){	
				DLLNode newn = initDLLNode(src,size);
				
				newn->next = n;
				newn->prev = n->prev;

				if (n->prev != NULL)
					n->prev->next = newn;
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
        if (ind >= l->length || ind < 0){
                fprintf(stderr, "Invalid index specified in set.\n");
        } else if (ind >= l->length/2){
                int i = l->length - 1;
                for (DLLNode n = l->tail; n != NULL; n = n->prev, i--){
                        if (i == ind){
				if (n->next != NULL)
					n->next->prev = n->prev;
				if (n->prev != NULL)
					n->prev->next = n->prev;
				if (n == l->head)
					l->head = n->next;
				if (n == l->tail)
					l->tail = n->prev;
				l->length--;
				freeDLLNode(n);
				return;
                        }
                }
        } else {
                int i = 0;
                for (DLLNode n = l->head; n != NULL; n = n->next, i++){
                        if (i == ind){
                                if (n->next != NULL)
                                        n->next->prev = n->prev;
                                if (n->prev != NULL)
                                        n->prev->next = n->prev;
                                if (n == l->head)
                                        l->head = n->next;
                                if (n == l->tail)
                                        l->tail = n->prev;
                                l->length--;
                                freeDLLNode(n);
                                return;
                        }
                }
        }
}

void printDiagsDLList(DLList l){
        for (int i = 0; i < 30; i++)
		printf("-");
        printf("\n");

        printf("List Length:%d\n",l->length);

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
