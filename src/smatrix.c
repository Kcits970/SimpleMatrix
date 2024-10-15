#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "smatrix.h"
#include "nstdmath.h"

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

static inline int __rcpair_cmp(int r1, int c1, int r2, int c2)
{
	return r1 == r2 ? c1 - c2 : r1 - r2;
}

/*
__smatrix_add: utility function to perform addition/subtraction between two sparse matrices.
	smat_a: first operand.
	smat_b: second operand.
	sign: assumed to be either 1 or -1. 1 is used for addition, -1 is used for subtraction.
	res: resulting sparse matrix.
*/
static void __smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b, int sign, smatrix_entry *res)
{
	res[0].r = smat_a[0].r;
	res[0].c = smat_a[0].c;

	int a_ptr = 1;
	int b_ptr = 1;
	int nzcnt = 0;
	int pos = 1;

	while (a_ptr <= smat_a[0].v && b_ptr <= smat_b[0].v)
	{
		int __state = __rcpair_cmp(smat_a[a_ptr].r, smat_a[a_ptr].c, smat_b[b_ptr].r, smat_b[b_ptr].c);

		// the two r-c indices are equal.
		if (__state == 0)
		{
			int __v = smat_a[a_ptr].v + sign*smat_b[b_ptr].v;

			// only store the entry if the result is non-zero.
			if (__v)
			{
				res[pos] = smat_a[a_ptr];
				res[pos].v = __v;
			}
			a_ptr++;
			b_ptr++;

			if (!__v)
				continue;
		}

		// the first r-c index predeces the second r-c index.
		else if (__state < 0)
			res[pos] = smat_a[a_ptr++];

		// the second r-c index predeces the first r-c index.
		else
		{
			res[pos] = smat_b[b_ptr++];
			res[pos].v *= sign;
		}

		nzcnt++;
		pos++;
	}

	while (a_ptr <= smat_a[0].v)
	{
		res[pos++] = smat_a[a_ptr++];
		nzcnt++;
	}

	while (b_ptr <= smat_b[0].v)
	{
		res[pos] = smat_b[b_ptr++];
		res[pos].v *= sign;
		nzcnt++;
		pos++;
	}

	res[0].v = nzcnt;
}

void smatrix_add(smatrix_entry *smat_a, smatrix_entry *smat_b, smatrix_entry *res)
{
	__smatrix_add(smat_a, smat_b, 1, res);
}

void smatrix_sub(smatrix_entry *smat_a, smatrix_entry *smat_b, smatrix_entry *res)
{
	__smatrix_add(smat_a, smat_b, -1, res);
}

void smatrix_print(smatrix_entry *smat)
{
	for (int i = 1; i <= smat[0].v; i++)
		printf("%d %d %d\n", smat[i].r, smat[i].c, smat[i].v);
	printf("%d rows, %d columns, %d non-zero entries\n", smat[0].r, smat[0].c, smat[0].v);
}
