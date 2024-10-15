#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "smatrix.h"

smatrix_entry* smatrix_new(int **mat, int m, int n)
{
	int sz = matrix_nzcnt(mat, m, n);
	smatrix_entry *smat = malloc(sizeof(smatrix_entry) * (sz+1));
	smat[0].r = m;
	smat[0].c = n;
	smat[0].v = sz;

	int pos = 1;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!mat[i][j])
				continue;

			smat[pos].r = i;
			smat[pos].c = j;
			smat[pos].v = mat[i][j];
			pos++;
		}
	}

	return smat;
}

void smatrix_free(smatrix_entry *smat)
{
	free(smat);
}

void smatrix_trans(smatrix_entry *smat, smatrix_entry *res)
{
	res[0].r = smat[0].c;
	res[0].c = smat[0].r;
	res[0].v = smat[0].v;

	int pos = 1;
	for (int i = 0; i < smat[0].c; i++)
	{
		for (int j = 1; j <= smat[0].v; j++)
		{
			if (smat[j].c != i)
				continue;

			res[pos].r = i;
			res[pos].c = smat[j].r;
			res[pos].v = smat[j].v;
			pos++;
		}
	}
}

/*
__smatrix_add: utility function to perform matrix addition/subtraction with two sparse matrices.
	smat_a: first operand.
	smat_b: second operand.
	sign: assumed to be either 1 or -1. 1 is used for addition, -1 is used for subtraction.
	res: resulting matrix.
*/
static void __smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b, int sign, int **res)
{
	matrix_init(res, smat_a[0].r, smat_a[0].c);

	for (int i = 1; i <= smat_a[0].v; i++)
		res[smat_a[i].r][smat_a[i].c] += smat_a[i].v;

	for (int i = 1; i <= smat_b[0].v; i++)
		res[smat_b[i].r][smat_b[i].c] += sign * smat_b[i].v;
}

void smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b, int **res)
{
	__smatrix_add(smat_a, smat_b, 1, res);
}

void smatrix_sub(smatrix_entry *smat_a, smatrix_entry *smat_b, int **res)
{
	__smatrix_add(smat_a, smat_b, -1, res);
}

void smatrix_mult(smatrix_entry *smat_a, smatrix_entry *smat_b, int **res)
{
	matrix_init(res, smat_a[0].r, smat_b[0].c);

	for (int i = 1; i <= smat_a[0].v; i++)
	{
		for (int j = 1; j <= smat_b[0].v; j++)
		{
			// if the row/column indices do not match, ignore and continue.
			if (smat_a[i].c != smat_b[j].r)
				continue;

			res[smat_a[i].r][smat_b[j].c] += smat_a[i].v * smat_b[j].v;
		}
	}
}

void smatrix_print(smatrix_entry *smat)
{
	for (int i = 1; i <= smat[0].v; i++)
		printf("%d %d %d\n", smat[i].r, smat[i].c, smat[i].v);
	printf("%d rows, %d columns, %d non-zero entries\n", smat[0].r, smat[0].c, smat[0].v);
}
