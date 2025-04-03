#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arr.h"

Array NewArray(const void **arr) {
	Array a = { 
		.arr = (void **)malloc(sizeof(void *) * 1),
		.idx = 0,
	};

	ConstructArrayMethods(&a);

	if(!arr) 
		return a;

	free(a.arr);
	a.arr = (void **)arr;
	while(arr[a.idx] != NULL)
		a.idx++;
	
	a.arr[a.idx] = NULL;
	return a;
}

void ConstructArrayMethods(Array *a) {
	a->Clear 			= ArrClear;
	a->Is				= IsCharInArray;
	a->IsInt			= IsIntInArray;
	a->Insert			= Array__Insert;
	a->Get 				= GetElement;
	a->Merge 			= Array_Merge;
	a->Append 			= Array__Append;
	a->Remove 			= Array__Remove;
	a->Join 			= Array__Join;
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

	a->arr = (void **)malloc(sizeof(void *) * 1);
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
	if(!a || !a->arr || idx <= 0)
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

int Array__Insert(Array *a, int pos, void *p) {
	if(!a || pos < 1 || !p)
		return 0;

	void **arr = (void **)malloc(sizeof(void *) * 1);
	int idx = 0;

	for(int i = 0; i < a->idx; i++) {
		arr[idx] = a->arr[i];
		idx++;
		arr = (void **)realloc(arr, sizeof(void *) * (idx + 1));

		if(i == pos)
		{
			arr[idx] = p;
			idx++;
			arr = (void **)realloc(arr, sizeof(void *) * (idx + 1));
		}
		arr[idx] = NULL;
	}

	if(a->arr)
		free(a->arr);

	a->arr = arr;
	a->idx = idx;

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

char *Array__Join(Array *a, char *delim) {
	char *buff = (char *)malloc(1);
	memset(buff, '\0', 1);
	int idx = 0;

	for(int i = 0; i < a->idx; i++) {
		if(!a->arr[i])
			break;

		idx += strlen((char *)a->arr[i]) + strlen(delim);
		buff = (char *)realloc(buff, idx + 1);
		strncat(buff, (char *)a->arr[i], strlen(a->arr[i]));
		if(i != a->idx - 1)
			strcat(buff, delim);

		a->arr[idx] = '\0';
	}

	return buff;
}

void DestructArray(Array *a, int elements, int arr) {
	if(a->arr && elements) {
		for(int i = 0; i < a->idx; i++) {
			if(a->arr[i]) {
				free(a->arr[i]);
				a->arr[i] = NULL;
			}
		}
	}

	if(arr) free(a->arr);
}
