#ifndef __MATRIX_H
#define __MATRIX_H

struct matrix
{
	// m: number of rows, n: number of columns.
	int m, n;
	int **mem;
};

typedef struct matrix matrix;

matrix* matrix_new(int, int);
void matrix_free(matrix*);
void matrix_init(matrix*);
void matrix_rand(matrix*);
void matrix_zrand(matrix*, int);
int matrix_nzcnt(matrix*);
matrix* matrix_add(matrix*, matrix*);
matrix* matrix_sub(matrix*, matrix*);
matrix* matrix_mult(matrix*, matrix*);
matrix* matrix_div(matrix*, matrix*);
void matrix_print(matrix*);

#endif
