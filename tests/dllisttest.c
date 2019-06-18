#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "dllist.h"
#include "tuple.h"
#include "complex.h"
#include "derefvoid.h"

bool testInitAndFree(){
	DLList l = initDLList();
	
	bool out = l->head == NULL && l->length == 0 && l->tail == NULL;
	
	free(l);

	return out;
}

bool testExpand(){
	DLList l = initDLList();

	int a = -1;
	double b = 101.1234;
	complex c = initComp(123.2, 12.3);
	tuple3(int, double, char) d = {12, 263.2342, 'c'};
	char e[6] = {'R', 'i', 'l', 'e', 'y', '\0'};

	addDLList(&a, sizeof(a), l);
	addDLList(&b, sizeof(b), l);
	addDLList(&c, sizeof(c), l);
	addDLList(&d, sizeof(d), l);
	addDLList(&e, sizeof(e), l);

	bool out = l->head != NULL && l->tail != NULL
		&& derefVoid(dataDLLNode(getDLList(0, l)), int) == a
		&& derefVoid(dataDLLNode(getDLList(1, l)), double) == b
		&& memcmp(dataDLLNode(getDLList(2, l)), &c, sizeof(c)) == 0
		&& memcmp(dataDLLNode(getDLList(3, l)), &d, sizeof(d)) == 0
		&& memcmp(dataDLLNode(getDLList(4, l)), &e, sizeof(e)) == 0
		&& l->length == 5;

	free(l);

	return out;
}

bool testClone(){
	DLList l1 = initDLList();
	DLList l2 = initDLList();
	
	int a = -1;
	double b = 101.1234;
	complex c = initComp(123.2, 12.3);
	tuple3(int, double, char) d = {12, 263.2342, 'c'};
	char e[6] = {'R', 'i', 'l', 'e', 'y', '\0'};

	addDLList(&a, sizeof(a), l1);
	addDLList(&b, sizeof(b), l1);
	addDLList(&c, sizeof(c), l1);
	addDLList(&d, sizeof(d), l1);
	addDLList(&e, sizeof(e), l1);
	
	DLList lc = cloneDLList(l1);

	bool b1 = l1->head != NULL && l1->tail != NULL
		&& derefVoid(dataDLLNode(getDLList(0, l1)), int) == a
		&& derefVoid(dataDLLNode(getDLList(1, l1)), double) == b
		&& memcmp(dataDLLNode(getDLList(2, l1)), &c, sizeof(c)) == 0
		&& memcmp(dataDLLNode(getDLList(3, l1)), &d, sizeof(d)) == 0
		&& memcmp(dataDLLNode(getDLList(4, l1)), &e, sizeof(e)) == 0
		&& lc->length == 5;


	bool b2 = lc->head != NULL && lc->tail != NULL
		&& derefVoid(dataDLLNode(getDLList(0, lc)), int) == a
		&& derefVoid(dataDLLNode(getDLList(1, lc)), double) == b
		&& memcmp(dataDLLNode(getDLList(2, lc)), &c, sizeof(c)) == 0
		&& memcmp(dataDLLNode(getDLList(3, lc)), &d, sizeof(d)) == 0
		&& memcmp(dataDLLNode(getDLList(4, lc)), &e, sizeof(e)) == 0
		&& lc->length == 5;

	freeDLList(lc);
	lc = cloneDLList(l2);

	bool b3 = l2->head == NULL && l2->tail == NULL &&
		l2->length == 0;

	bool b4 = lc->head == NULL && lc->tail == NULL &&
		lc->length == 0;
		
	freeDLList(lc);
	freeDLList(l1);
	freeDLList(l2);

	return b1 && b2 && b3 && b4;
}

int main(void){
	printf("Test DLList\n");
	printf("InitAndFree: %d\n", testInitAndFree());
	printf("Expand: %d\n", testExpand());
	printf("Clone: %d\n", testClone());
	return 0;
}
