#ifndef __SMATRIX_H
#define __SMATRIX_H

#include <stdlib.h>
#include "matrix.h"

// sparse matrix entry.
struct smatrix_entry
{
	// row, column, value;
	int r, c, v;
};

typedef struct smatrix_entry smatrix_entry;

smatrix_entry* smatrix_new(int**, int, int);
void smatrix_free(smatrix_entry*);
void smatrix_trans(smatrix_entry*, smatrix_entry*);
void smatrix_add(smatrix_entry*, smatrix_entry*, int**);
void smatrix_sub(smatrix_entry*, smatrix_entry*, int**);
void smatrix_mult(smatrix_entry*, smatrix_entry*, int**);
void smatrix_print(smatrix_entry*);

#endif
