#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "smatrix.h"

smatrix_entry* smatrix_new(matrix *mat)
{
	int sz = matrix_nzcnt(mat);
	smatrix_entry *smat = malloc(sizeof(smatrix_entry) * (sz+1));
	smat[0].r = mat->m;
	smat[0].c = mat->n;
	smat[0].v = sz;

	int pos = 1;
	for (int i = 0; i < mat->m; i++)
	{
		for (int j = 0; j < mat->n; j++)
		{
			if (!mat->mem[i][j])
				continue;

			smat[pos].r = i;
			smat[pos].c = j;
			smat[pos].v = mat->mem[i][j];
			pos++;
		}
	}

	return smat;
}

void smatrix_free(smatrix_entry *smat)
{
	free(smat);
}

smatrix_entry* smatrix_trans(smatrix_entry *smat)
{
	smatrix_entry *res = malloc(sizeof(smatrix_entry) * (smat[0].v+1));
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

	return res;
}

/*
__smatrix_add: utility function to perform matrix addition/subtraction with two sparse matrices.
	smat_a: first operand.
	smat_b: second operand.
	sign: assumed to be either 1 or -1. 1 is used for addition, -1 is used for subtraction.
*/
static matrix* __smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b, int sign)
{
	matrix *res = matrix_new(smat_a[0].r, smat_a[0].c);
	matrix_init(res);

	for (int i = 1; i <= smat_a[0].v; i++)
		res->mem[smat_a[i].r][smat_a[i].c] += smat_a[i].v;

	for (int i = 1; i <= smat_b[0].v; i++)
		res->mem[smat_b[i].r][smat_b[i].c] += sign * smat_b[i].v;

	return res;
}

matrix* smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b)
{
	return __smatrix_add(smat_a, smat_b, 1);
}

matrix* smatrix_sub(smatrix_entry *smat_a, smatrix_entry *smat_b)
{
	return __smatrix_add(smat_a, smat_b, -1);
}

matrix* smatrix_mult(smatrix_entry *smat_a, smatrix_entry *smat_b)
{
	matrix *res = matrix_new(smat_a[0].r, smat_b[0].c);
	matrix_init(res);

	for (int i = 1; i <= smat_a[0].v; i++)
	{
		for (int j = 1; j <= smat_b[0].v; j++)
		{
			// if the row/column indices do not match, ignore and continue.
			if (smat_a[i].c != smat_b[j].r)
				continue;

			res->mem[smat_a[i].r][smat_b[j].c] += smat_a[i].v * smat_b[j].v;
		}
	}

	return res;
}

void smatrix_print(smatrix_entry *smat)
{
	for (int i = 1; i <= smat[0].v; i++)
		printf("%d %d %d\n", smat[i].r, smat[i].c, smat[i].v);
	printf("%d rows, %d columns, %d non-zero entries\n", smat[0].r, smat[0].c, smat[0].v);
}
