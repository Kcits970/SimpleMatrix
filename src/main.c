#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

int main()
{
	srand(time(0));

	int **a = matrix_new(2, 3);
	int **b = matrix_new(3, 2);
	matrix_rand(a, 2, 3);
	matrix_rand(b, 3, 2);

	puts("matrix a");
	matrix_print(a, 2, 3);
	puts("matrix b");
	matrix_print(b, 3, 2);

	int **c = matrix_new(2, 2);
	matrix_mult(a, b, c, 2, 3, 2);
	puts("matrix c = a * b");
	matrix_print(c, 2, 2);

	smatrix_entry *sa = smatrix_new(a, 2, 3);
	smatrix_entry *sb = smatrix_new(b, 3, 2);

	puts("sparse matrix a");
	smatrix_print(sa);
	puts("sparse matrix b");
	smatrix_print(sb);

	return 0;
}
