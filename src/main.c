#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

int main()
{
	srand(time(0));

	int **a = matrix_new(3, 3);
	int **b = matrix_new(3, 3);
	matrix_rand(a, 3, 3);
	matrix_rand(b, 3, 3);

	puts("matrix a");
	matrix_print(a, 3, 3);
	puts("matrix b");
	matrix_print(b, 3, 3);

	int **c = matrix_new(3, 3);
	int **d = matrix_new(3, 3);
	int **e = matrix_new(3, 3);

	smatrix_entry *sa = smatrix_new(a, 3, 3);
	smatrix_entry *sb = smatrix_new(b, 3, 3);
	
	puts("sparse matrix a");
	smatrix_print(sa);
	puts("sparse matrix b");
	smatrix_print(sb);
	
	smatrix_add(sa, sb, c);
	smatrix_sub(sa, sb, d);
	smatrix_mult(sa, sb, e);

	puts("matrix c = a + b");
	matrix_print(c, 3, 3);
	puts("matrix d = a - b");
	matrix_print(d, 3, 3);
	puts("matrix e = a * b");
	matrix_print(e, 3, 3);

	return 0;
}
