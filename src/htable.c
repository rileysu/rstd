#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"
#include "arrlist.h"
#include "datatypes.h"

static void placeHTable(void *key, void *value, HTable ht){
	unsigned int pos = ht->hash(key, ht->keysize, ht->length);

        for (int i = pos; i < ht->length; i++){
                if (!getPopulatedHTable(getArrList(i, ht->l), ht)){
                        char *el = (char*)getArrList(i, ht->l);
                        *(bool*)el = TRUE;
                        memcpy(el + sizeof(bool), key, ht->keysize);
                        memcpy(el + sizeof(bool) + ht->keysize, value, ht->valuesize);
                        return;
                }
        }

        for (int i = 0; i < pos; i++){
                if (!getPopulatedHTable(getArrList(i, ht->l), ht)){
                        char *el = (char*)getArrList(i, ht->l);
                        *(bool*)el = TRUE;
                        memcpy(el + sizeof(bool), key, ht->keysize);
                        memcpy(el + sizeof(bool) + ht->keysize, value, ht->valuesize);
                        return;
                }
        }

        printf("The impossible happened!\n");
}

HTable initHTable(int length, size_t keysize, size_t valuesize, unsigned int (*hash)(void*, size_t, int)){
	HTable ht = malloc(sizeof(struct HTable_t));
	
	ht->l = initArrList(length, sizeof(bool) + keysize + valuesize);
	ht->l->clength = length;
	memset(ht->l->head, 0, (sizeof(bool) + keysize + valuesize) * length);

	ht->keysize = keysize;
	ht->valuesize = valuesize;
	ht->clength = 0;
	ht->length = length;
	ht->hash = hash;

	return ht;
}

void freeHTable(HTable ht){
	freeArrList(ht->l);
	free(ht);
}

void expandHTable(int length, HTable ht){
	ArrList tl = cloneArrList(ht->l);
	expandArrList(length, ht->l);
	ht->l->clength = length;
	ht->length = length;
	memset(ht->l->head, 0, ht->l->nsize * ht->l->length);

	for(int i = 0; i < tl->length; i++){
		void *el = getArrList(i, tl);
		if (getPopulatedHTable(el, ht)){
			//unsigned int pos = ht->hash(getKeyHTable(el, ht), ht->keysize, ht->length);
			//memset(getArrList(i, ht->l), 0, ht->l->nsize);
			placeHTable(getKeyHTable(el, ht), getValueHTable(el, ht), ht);
		}
	}

	freeArrList(tl);
}

void setHTable(void *key, void *value, HTable ht){
	if (ht->clength == ht->length)
		expandHTable(ht->length*2, ht);

	void *el = getHTable(key, ht);

	if (el == NULL){
		placeHTable(key, value, ht);	
		ht->clength++;
	} else
		memcpy(el, value, ht->valuesize);
}

void *getHTable(void *key, HTable ht){
	unsigned int pos = ht->hash(key, ht->keysize, ht->length);

	for (int i = pos; i < ht->length; i++){
		if (memcmp(getKeyHTable(getArrList(i, ht->l), ht), key, ht->keysize) == 0){
			return getValueHTable(getArrList(i, ht->l), ht);
		}
	}
	for (int i = 0; i < pos; i++){
		if (memcmp(getKeyHTable(getArrList(i, ht->l), ht), key, ht->keysize) == 0){
			return getValueHTable(getArrList(i, ht->l), ht);
		}
	}

	return NULL;
}

void delHTable(void *key, HTable ht){
	void *el = getHTable(key, ht);
	if (el != NULL)
		memset(el, 0, sizeof(bool) + ht->keysize + ht->valuesize);
}

void printDiagsHTable(HTable ht){
	for (int i = 0; i < 30; i++)
		printf("-");
	printf("\n");
	
	printf("HashTable Length:%d\n", ht->length);
	printf("HashTable CLength:%d\n", ht->clength);

	printf("Contains:\n\n");
	for (int i = 0; i < ht->length; i++){
		printf("Table Hash:%d\n", i);
		printf("Calculated Hash:%u\n", ht->hash(getKeyHTable(getArrList(i, ht->l), ht), ht->keysize, ht->length));
		printf("Populated: %d\n", derefVoid(getArrList(i, ht->l), bool));
		printf("Key: ");
		for (int j = 0; j < ht->keysize; j++)
			printf("%02x", *((unsigned char*)getArrList(i, ht->l) + sizeof(bool) + j));
		printf("\n");
		printf("Value: ");
		for (int j = 0; j < ht->valuesize; j++)
			printf("%02x", *((unsigned char*)getArrList(i, ht->l) + sizeof(bool) + ht->keysize + j));
		printf("\n\n");
	}
	
	for (int i = 0; i < 30; i++)
		printf("-");
	printf("\n");
}
