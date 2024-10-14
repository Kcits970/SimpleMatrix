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

void smatrix_print(smatrix_entry *smat)
{
	for (int i = 1; i <= smat[0].v; i++)
		printf("%d %d %d\n", smat[i].r, smat[i].c, smat[i].v);
	printf("%d rows, %d columns, %d non-zero entries\n", smat[0].r, smat[0].c, smat[0].v);
}
