#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "array.h"

Array NewArray(const void **arr) {
	if(!arr) {
		return (Array){
			.arr = (void **)malloc(sizeof(void *) * 1),
			.idx = 0
		};
	}

	Array a = { .idx = 0 };
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
	if(!a || a->arr || !element)
		return 0;

	a->arr[a->idx] = element;
	a->idx++;
	a->arr = (void **)realloc(a->arr, sizeof(void *) * (a->idx + 1));
	return 1;
}

int Array__Remove(Array *a, int idx) {
	if(!a || !a->arr || idx >= a->idx)
		return 0;


	void **new = (void **)malloc(sizeof(void *) * 1);
	int n = 0;

	for(int i = 0; i < a->idx; i++) {
		if(i == idx)
			continue;

		new[n] = a->arr[i];
		n++;
		new = (void **)realloc(new, sizeof(void *) * (n + 1));
	}
}