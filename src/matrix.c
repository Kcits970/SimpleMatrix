#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "nstdmath.h"
#define ENTRY_MAX 16

matrix* matrix_new(int m, int n)
{
	matrix *mat = malloc(sizeof(matrix));
	mat->m = m;
	mat->n = n;
	mat->mem = malloc(sizeof(int*) * m);
	for (int i = 0; i < m; i++)
		mat->mem[i] = malloc(sizeof(int) * n);

	return mat;
}

void matrix_free(matrix *mat)
{
	for (int i = 0; i < mat->m; i++)
		free(mat->mem[i]);
	free(mat->mem);
	free(mat);
}

// matrix_init: completely zeroes-out the given matrix.
void matrix_init(matrix *mat)
{
	for (int i = 0; i < mat->m; i++)
	{
		for (int j = 0; j < mat->n; j++)
		{
			mat->mem[i][j] = 0;
		}
	}
}

// matrix_rand: randomizes the entries of the given matrix.
void matrix_rand(matrix *mat)
{
	for (int i = 0; i < mat->m; i++)
	{
		for (int j = 0; j < mat->n; j++)
		{
			mat->mem[i][j] = rand() % ENTRY_MAX - ENTRY_MAX/2;
		}
	}
}

// matrix_nzcnt(non-zero count): returns the number of non-zero entries in the given matrix.
int matrix_nzcnt(matrix *mat)
{
	int cnt = 0;

	for (int i = 0; i < mat->m; i++)
	{
		for (int j = 0; j < mat->n; j++)
		{
			cnt += mat->mem[i][j] != 0;
		}
	}

	return cnt;
}

matrix* matrix_add(matrix *mat_a, matrix *mat_b)
{
	matrix *res = matrix_new(mat_a->m, mat_a->n);

	for (int i = 0; i < mat_a->m; i++)
	{
		for (int j = 0; j < mat_a->n; j++)
		{
			res->mem[i][j] = mat_a->mem[i][j] + mat_b->mem[i][j];
		}
	}

	return res;
}

matrix* matrix_sub(matrix *mat_a, matrix *mat_b)
{
	matrix *res = matrix_new(mat_a->m, mat_a->n);

	for (int i = 0; i < mat_a->m; i++)
	{
		for (int j = 0; j < mat_a->n; j++)
		{
			res->mem[i][j] = mat_a->mem[i][j] - mat_b->mem[i][j];
		}
	}

	return res;
}

matrix* matrix_mult(matrix *mat_a, matrix *mat_b)
{
	matrix *res = matrix_new(mat_a->m, mat_b->n);

	for (int i = 0; i < mat_a->m; i++)
	{
		for (int j = 0; j < mat_b->n; j++)
		{
			// dot product.
			int dprod = 0;
			for (int k = 0; k < mat_a->n; k++)
				dprod += mat_a->mem[i][k] * mat_b->mem[k][j];

			res->mem[i][j] = dprod;
		}
	}

	return res;
}

matrix* matrix_div(matrix *mat_a, matrix *mat_b)
{
	matrix *res = matrix_new(mat_a->m, mat_a->n);

	for (int i = 0; i < mat_a->m; i++)
	{
		for (int j = 0; j < mat_a->n; j++)
		{
			res->mem[i][j] = nstd_idiv(mat_a->mem[i][j], mat_b->mem[i][j]);
		}
	}

	return res;
}

void matrix_print(matrix *mat)
{
	for (int i = 0; i < mat->m; i++)
	{
		for (int j = 0; j < mat->n; j++)
			printf("%d ", mat->mem[i][j]);

		puts("");
	}
}
