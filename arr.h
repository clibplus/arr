/*
*
	Use Example:

	void debug_arr(Array *a) {
		for(int i = 0; i < a->idx; i++)
			printf("[%d] %s\n", i, (char *)a->arr[i]);
	}

	int main(int argc, char *argv[]) {
		Array args = NewArray(NULL);

		int chk = args.Append(&args, (void *)strdup("GAY"));
		chk = args.Append(&args, (void *)strdup("SEX"));
		chk = args.Append(&args, (void *)strdup("NIG"));
		printf("%ld\n", args.idx);
		debug_arr(&args);

		printf("\n\n");
		chk = args.Remove(&args, 1);
		debug_arr(&args);

		printf("%d\n", args.IsCharInArray(&args, "NIG"));
		return 0;
	}

*/
#pragma once

typedef struct Array {
	void 		**arr;
	long		idx;

	int 		(*Clear)			(struct Array *a);
	int			(*Is)				(struct Array *a, void *sub);
	int			(*IsInt)			(struct Array *a, void *num);
	int 		(*Push) 			(struct Array *a, void *v);
	int 		(*Pop)				(struct Array *a);
	int 		(*IndexOf)			(struct Array *a, void *p);
	int 		(*Sort)				(struct Array *a);
	int 		(*Reverse)			(struct Array *a);

	void		*(*Get)				(struct Array *a, int idx);
	int			(*Merge)			(struct Array *a, void **arr);
	int			(*Append)			(struct Array *a, void *element);
	int 		(*Remove)			(struct Array *a, int idx);
	void		(*Destruct)			(struct Array *a);
} Array;

//
//			| - > Create a new Array intanse
//			| - > Returns the struct with the array provided or a new array
//
Array 		NewArray(const void **arr);

//
//			| - > Clear the array buffer
//			| - > Returns 1 upon success or 0 upon failure
//
int 		ArrClear(Array *a);

//
//			| - > Check if an element in the array matches the char pointer provided 
//			| - > Returns 1 upon success or 0 upon failure
//
int 		IsCharInArray(Array *a, void *sub);

//
//			| - > Check if an element in the array matches the int pointer provided 
//			| - > Returns 1 upon success or 0 upon failure
//
int 		IsIntInArray(Array *a, void *sub);

//
//			| - > Get an element from the array with the position provided
//			| - > Returns the element upon success or NULL upon failure
//
void 		*GetElement(Array *a, int idx);
//
//			| - > Merge an array to the current array
//			| - > Returns 1 on success, 0 on failure
//
int 		Array_Merge(Array *a, void **arr);

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
