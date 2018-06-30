#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"
#include "dllist.h"

HTNode initHTNode(void *key, size_t keysize, void *value, size_t valuesize, DLList l){
	addDLList(NULL, sizeof(struct HTNode_t) + keysize + valuesize, l);
	DLLNode dn = l->tail;
	HTNode n = (HTNode) dataDLLNode(dn);
	n->keysize = keysize;
	n->valuesize = valuesize;
	memcpy(keyHTNode(n), key, keysize);
	memcpy(valueHTNode(n), value, valuesize);
	return n;
}

HTable initHTable(int length, unsigned int (*hash)(void*, size_t, int)){
	HTable ht = malloc(sizeof(struct HTable_t));
	ht->arr = malloc(sizeof(DLList) * length);
	for (int i = 0; i < length; i++)
		ht->arr[i] = initDLList();
	ht->clength = 0;
	ht->length = length;
	ht->hash = hash;
}

void freeHTNode(HTNode n, DLList l){
	delNodeDLList(((DLLNode) n) - 1, l);
}

void freeHTable(HTable ht){
	for (int i = 0; i < ht->length; i++)
		freeDLList(ht->arr[i]);
	free(ht->arr);
	free(ht);
}

void addHTable(void *key, size_t keysize, void *value, size_t valuesize, HTable ht){
	unsigned int hashval = ht->hash(key, keysize, ht->length);
	DLList l = ht->arr[hashval];
	HTNode n = NULL;
	
	forDLList(i,l){
		if (keysize == ((HTNode) dataDLLNode(i))->keysize && memcmp(key, keyHTNode(dataDLLNode(i)), keysize) == 0){
			n = (HTNode) dataDLLNode(i);
			break;
		}
	}

	if (n == NULL){
		initHTNode(key, keysize, value, valuesize, ht->arr[hashval]);
		ht->clength++;
	} else {
		freeHTNode(n, ht->arr[hashval]);
		initHTNode(key, keysize, value, valuesize, ht->arr[hashval]);
	}
}

HTNode getHTable(void *key, size_t keysize, HTable ht){
	unsigned int hashval = ht->hash(key, keysize, ht->length);
	DLList l = ht->arr[hashval];
	
	forDLList(i,l)
		if (keysize == ((HTNode) dataDLLNode(i))->keysize && memcmp(key, keyHTNode(dataDLLNode(i)), keysize) == 0)
			return (HTNode) dataDLLNode(i);
	return NULL;
}

void remHTable(void *key, size_t keysize, HTable ht){
	unsigned int hashval = ht->hash(key, keysize, ht->length);
	HTNode n = getHTable(key, keysize, ht);
	
	if (n != NULL)
		freeHTNode(n, ht->arr[hashval]);
}

void printDiagsHTable(HTable ht){
	for (int i = 0; i < 30; i++)
		printf("-");
	printf("\n");
	
	printf("HashTable Length:%d\n", ht->length);
	printf("HashTable CLength:%d\n", ht->clength);

	printf("Contains:\n");
	for (int i = 0; i < ht->length; i++){
		if (ht->arr[i]->length != 0){
			printf("Table Hash:%d\n", i);
			printDiagsDLList(ht->arr[i]);
		}
	}
	
	for (int i = 0; i < 30; i++)
		printf("-");
	printf("\n");
}
