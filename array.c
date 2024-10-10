#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array.h"

Array NewArray(const void **arr) {
	Array a = { 
		.idx = 0,

		.Get 		= GetElement,
		.Append 	= Array__Append,
		.Remove 	= Array__Remove,
		.Destruct	= DestructArray
	};

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

void *GetElement(Array *a, int idx) {
	if(!a || !a->arr)
		return NULL;

	if(idx >= a->idx)
		return NULL;

	return a->arr[idx];
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
