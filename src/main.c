#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

int main()
{
	srand(time(0));

	matrix *a = matrix_new(3, 3);
	matrix *b = matrix_new(3, 3);
	matrix_rand(a);
	matrix_rand(b);

	puts("a matrix");
	matrix_print(a);
	puts("b matrix");
	matrix_print(b);

	matrix *c = matrix_add(a, b);
	matrix *d = matrix_sub(a, b);
	matrix *e = matrix_mult(a, b);

	puts("c matrix");
	matrix_print(c);
	puts("d matrix");
	matrix_print(d);
	puts("e matrix");
	matrix_print(e);

	matrix_free(a);
	matrix_free(b);
	matrix_free(c);
	matrix_free(d);
	matrix_free(e);
	return 0;
}
