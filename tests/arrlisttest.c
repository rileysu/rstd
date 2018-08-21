#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "arrlist.h"

bool testInitAndFree(){
	ArrList l = initArrList(10, sizeof(int));
	bool test = l->head != NULL && l->nsize == sizeof(int) && l->clength == 0 && l->length == 10;
	freeArrList(l);
	return test;
}

bool testExpandArrList(){
	ArrList l = initArrList(4, sizeof(int));
	int a = 4;
	int b = 5;
	addArrList(&a, l);
	addArrList(&b, l);
	expandArrList(9, l);
	bool test = l->head != NULL && l->nsize == sizeof(int) && l->clength == 2 && l->length == 9 &&
		*((int*)l->head) == 4 && *((int*)l->head + 1) == 5;
	freeArrList(l);
	return test;
}

bool testCloneArrList(){
	ArrList il = initArrList(4, sizeof(int));
	ArrList dl = initArrList(2, sizeof(double));
	ArrList cl = initArrList(6, sizeof(char));
	ArrList el = initArrList(8, sizeof(complex));
	
	int ai = 1000000000;
	int bi = -2000000000;
	int ci = 0;
	int di = 123456789;
	addArrList(&ai, il);
	addArrList(&bi, il);
	addArrList(&ci, il);
	addArrList(&di, il);
	
	double ad = 1.2334;
	double bd = 1000001.23424;
	double cd = 3.1415926;
	addArrList(&ad, dl);
	addArrList(&bd, dl);
	addArrList(&cd, dl);

	char str[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
	addArrList(&str[0], cl);
	addArrList(&str[1], cl);
	addArrList(&str[2], cl);
	addArrList(&str[3], cl);
	addArrList(&str[4], cl);
	addArrList(&str[5], cl);
	addArrList(&str[6], cl);
	addArrList(&str[7], cl);
	addArrList(&str[8], cl);
	addArrList(&str[9], cl);
	addArrList(&str[10], cl);
	addArrList(&str[11], cl);
	addArrList(&str[12], cl);

	ArrList l = cloneArrList(il);
	bool a = l->head != NULL && l->nsize == sizeof(int) && l->clength == 4 && l->clength == 4 && *(int*)getArrList(0, l) == 1000000000 && *(int*)getArrList(1, l) == -2000000000 && *(int*)getArrList(2, l) == 0 && *(int*)getArrList(3, l) == 123456789;
	freeArrList(l);

	l = cloneArrList(dl);
	bool b = l->head != NULL && l->nsize == sizeof(double) && l->clength == 3 && l->length == 4 && *(double*)getArrList(0, l) == 1.2334 && *(double*)getArrList(1, l) == 1000001.23424 && *(double*)getArrList(2, l) == 3.1415926;
	freeArrList(l);

	l = cloneArrList(cl);
	bool c = l->head != NULL && l->nsize == sizeof(char) && l->clength == 13 && l->length == 24 && strcmp("Hello World!", l->head) == 0;
	freeArrList(l);

	l = cloneArrList(el);
	bool d = l->head != NULL && l->nsize == sizeof(complex) && l->clength == 0 && l->length == 8;
	freeArrList(l);

	freeArrList(il);
	freeArrList(dl);
	freeArrList(cl);
	freeArrList(el);

	return a && b && c && d;
}

int main(void){

	printf("Test ArrList\n");
	printf("Init and Free: %d\n", testInitAndFree());
	printf("Expand: %d\n", testExpandArrList());
	printf("Clone: %d\n", testCloneArrList());

	return 0;
}
