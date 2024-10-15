#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "nstdmath.h"
#define ENTRY_MAX 16

int** matrix_new(int m, int n)
{
	int **mat = malloc(sizeof(int*) * m);
	for (int i = 0; i < m; i++)
		mat[i] = malloc(sizeof(int) * n);

	return mat;
}

void matrix_free(int **mat, int m)
{
	for (int i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
}

// matrix_rand: randomizes the entries of the given matrix.
void matrix_rand(int **mat, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat[i][j] = rand() % ENTRY_MAX - ENTRY_MAX/2;
		}
	}
}

// matrix_nzcnt(non-zero count): returns the number of non-zero entries in the given matrix.
int matrix_nzcnt(int **mat, int m, int n)
{
	int cnt = 0;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cnt += mat[i][j] != 0;
		}
	}

	return cnt;
}

void matrix_add(int **mat_a, int **mat_b, int **mat_res, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat_res[i][j] = mat_a[i][j] + mat_b[i][j];
		}
	}
}

void matrix_sub(int **mat_a, int **mat_b, int **mat_res, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat_res[i][j] = mat_a[i][j] - mat_b[i][j];
		}
	}
}

void matrix_mult(int **mat_a, int **mat_b, int **mat_res, int m, int n, int p)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			// dot product.
			int dprod = 0;
			for (int k = 0; k < n; k++)
				dprod += mat_a[i][k] * mat_b[k][j];

			mat_res[i][j] = dprod;
		}
	}
}

void matrix_div(int **mat_a, int **mat_b, int **mat_res, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mat_res[i][j] = nstd_idiv(mat_a[i][j], mat_b[i][j]);
		}
	}
}

void matrix_print(int **mat, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", mat[i][j]);

		puts("");
	}
}
