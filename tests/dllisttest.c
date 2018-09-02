#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "dllist.h"
#include "tuple.h"
#include "complex.h"
#include "derefvoid.h"


bool testCloneDLList(){
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

	bool b1 = lc->head != NULL && lc->tail != NULL
		&& derefVoid(dataDLLNode(getDLList(0, lc)), int) == a
		&& derefVoid(dataDLLNode(getDLList(1, lc)), double) == b
		&& memcmp(dataDLLNode(getDLList(2, lc)), &c, sizeof(c)) == 0
		&& memcmp(dataDLLNode(getDLList(3, lc)), &d, sizeof(d)) == 0
		&& memcmp(dataDLLNode(getDLList(4, lc)), &e, sizeof(e)) == 0
		&& lc->length == 5;

	freeDLList(lc);
	lc = cloneDLList(l2);

	bool b2 = lc->head == NULL && lc->tail == NULL &&
		lc->length == 0;
		
	freeDLList(lc);
	freeDLList(l1);
	freeDLList(l2);

	return b1 && b2;
}

int main(void){
	printf("Test DLList\n");
	printf("Clone: %d\n", testCloneDLList());

	return 0;
}
