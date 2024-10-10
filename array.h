#pragma once

typedef struct Array {
	void 		**arr;
	long		idx;

	int			(*InArray)	(struct Array *a, void *sub);
	void		*(*Get)		(struct Array *a, int idx);
	int			(*Append)	(struct Array *a, void *element);
	int 		(*Remove)	(struct Array *a, int idx);
	void		(*Destruct)	(struct Array *a);
} Array;

//
//			| - > Create a new Array intanse
//			| - > Returns the struct with the array provided or a new array
//
Array 		NewArray(const void **arr);

//
//			| - > Check if an element in the array matches the provided data
//			| - > Returns 1 upon success or 0 upon failure
//
int 		IsInArray(Array *a, void *sub);

//
//			| - > Get an element from the array with the position provided
//			| - > Returns the element upon success or NULL upon failure
//
void 		*GetElement(Array *a, int idx);

//
//			| - > Append an element to the array
//			| - > Returns 1 on success, 0 on failure and -1 for memory issue
//
int 		Array__Append(Array *a, void *element);

//
//			| - > Remove an element from array with position provided
//			| - > Returns 1 upon success or 0 upon failure
//
int 		Array__Remove(Array *a, int idx);

//
//			| -> Destroy the array
//
void 		DestructArray(Array *a);
