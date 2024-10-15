#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

int main()
{
	srand(time(0));

	int **a = matrix_new(2, 3);
	int **b = matrix_new(2, 3);
	matrix_rand(a, 2, 3);
	matrix_rand(b, 2, 3);

	puts("matrix a");
	matrix_print(a, 2, 3);
	puts("matrix b");
	matrix_print(b, 2, 3);

	smatrix_entry *sa = smatrix_new(a, 2, 3);
	smatrix_entry *sb = smatrix_new(b, 2, 3);
	smatrix_entry *sc = malloc(sizeof(smatrix_entry) * 10);
	smatrix_entry *sd = malloc(sizeof(smatrix_entry) * 10);
	smatrix_add(sa, sb, sc);
	smatrix_sub(sa, sb, sd);

	puts("sparse matrix a");
	smatrix_print(sa);
	puts("sparse matrix b");
	smatrix_print(sb);
	puts("sparse matrix c");
	smatrix_print(sc);
	puts("sparse matrix d");
	smatrix_print(sd);

	return 0;
}
