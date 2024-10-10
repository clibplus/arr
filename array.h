#pragma once

typedef struct Array {
	void 		**arr;
	long		idx;
} Array;

Array NewArray(const void **arr);
