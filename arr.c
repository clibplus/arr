#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arr.h"

Array NewArray(const void **arr) {
	Array a = { 
		.idx = 0,
	};

	ConstructArrayMethods(&a);

	if(!arr) {
		a.arr = (void **)malloc(sizeof(void *) * 1);
		return a;
	}

	while(arr[a.idx] != NULL) {
		a.arr[a.idx] = (void *)arr[a.idx];
		a.idx++;
		a.arr = (void **)realloc(a.arr, sizeof(void *) * (a.idx + 1));
	}

	a.arr[a.idx] = NULL;
	return a;
}

sArr NewStackArray(void **arr) {
	if(!arr)
		return ((sArr){ .idx = 0 });

	sArr a = { .arr = arr };
	ConstructArrayMethods(&a);

	int i = 0;
	while(arr[i] != NULL) i++;

	if(i == 1 && arr[0] == NULL)
		return ((sArr){ .idx = 0 });

	a->idx = i;

	return a;
}

void ConstructArrayMethods(Array *a) {
	a->Clear 			= ArrClear;
	a->IsCharInArray	= IsCharInArray;
	a->IsIntInArray		= IsIntInArray;
	a->Get 				= GetElement;
	a->Merge 			= Array_Merge;
	a->Append 			= Array__Append;
	a->Remove 			= Array__Remove;
	a->Destruct			= DestructArray;
}

int ArrClear(Array *a) {
	if(!a)
		return 0;

	for(int i = 0; i < a->idx; i++) {
		free(a->arr[i]);
		a->arr[i] = NULL;
	}

	free(a->arr);

	a->arr = (void **)malloc(sizeof(void *) * 1));
	a->idx = 0;

	return 1;
}

int IsCharInArray(Array *a, void *sub) {
	for(int i = 0; i < a->idx; i++)
		if(!strcmp(a->arr[i], sub))
			return i;

	return -1;
}

int IsIntInArray(Array *a, void *sub) {
	for(int i = 0; i < a->idx; i++) {
		if(*(int *)a->arr[i] == *(int *)sub)
			return i;
	}

	return -1;
}

void *GetElement(Array *a, int idx) {
	if(!a || !a->arr)
		return NULL;

	if(idx >= a->idx)
		return NULL;

	return a->arr[idx];
}

int Array_Merge(Array *a, void **arr) {
	if(!a)
		return 0;

	int i = 0;
	while(arr[i] != NULL) {
		Array__Append(a, arr[i]);
		i++;
	}

	return 1;
}

int Array__Append(Array *a, void *element) {
	if(!a || !a->arr || !element)
		return 0;

	a->arr[a->idx] = element;
	a->idx++;
	a->arr = (void **)realloc(a->arr, sizeof(void *) * (a->idx + 1));
	return 1;
}

int Array__Remove(Array *a, int idx) {
	if(!a || !a->arr || idx >= a->idx)
		return 0;

	void **new = (void **)malloc(sizeof(void *) * (a->idx - 1));
	if(!new)
		return -1;

	int n = 0;
	for(int i = 0; i < a->idx; i++) {
		if(i == idx)
			continue;

		new[n] = a->arr[i];
		n++;
	}

	free(a->arr);
	a->arr = new;
	a->idx--;

	return 1;
}

void DestructArray(Array *a) {
	if(a->arr) {
		for(int i = 0; i < a->idx; i++) {
			if(a->arr[i]) {
				free(a->arr[i]);
				a->arr[i] = NULL;
			}
		}
	}
}
