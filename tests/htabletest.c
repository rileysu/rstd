#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "htable.h"

unsigned int hash(void *src, size_t size, int range){
	unsigned int chash = 0;
	char *csrc = (char*) src;
	for (int i = 0; i < size; i++)
		chash = 31 * chash ^ csrc[i];
	return (chash % range);
}

bool testInitAndFree(){
	HTable ht = initHTable(4, sizeof(int), sizeof(double), &hash);
	bool testa = ht->l->length == 4 && ht->l->clength == 4 && ht->keysize == sizeof(int) && ht->valuesize == sizeof(double) && ht->length == 4 && ht->clength == 0;
	//printDiagsHTable(ht);
	freeHTable(ht);
	return testa;
}

bool testSet(){
	HTable ht = initHTable(1, sizeof(char), sizeof(int), &hash);
	char ac = '>';
	char bc = '0';
	char cc = 'q';
	char dc = 'L';
	char ec = 'Q';
	int ai = -1;
	int bi = -2;
	int ci = -3;
	int di = -4;
	int ei = -5;

	setHTable(&ac, &ai, ht);
	setHTable(&bc, &bi, ht);
	setHTable(&cc, &ci, ht);
	setHTable(&dc, &di, ht);
	setHTable(&ec, &ei, ht);
	setHTable(&bc, &ai, ht);

	bool testa = TRUE;

	//printDiagsHTable(ht);
	freeHTable(ht);
	return testa;
}

int main(void){
	printf("Test HTable\n");
	printf("Init and Free: %d\n", testInitAndFree());
	printf("Set: %d\n", testSet());

	return 0;
}
