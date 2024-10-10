#pragma once

typedef struct Array {
	void 		**arr;
	long		idx;

	void		*(*Get)		(Array *a, int idx);
	int			(*Append)	(Array *a, void *element);
	int 		(*Remove)	(Array *a, int idx);
	void		(*Destruct)	(Array *a);
} Array;

Array NewArray(const void **arr);
void *GetElement(Array *a, int idx);
int Array__Append(Array *a, void *element);
int Array__Remove(Array *a, int idx);
void DestructArray(Array *a);
