#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

void test_normal_binary(int size, matrix* (*op)(matrix*, matrix*), const char *name)
{
	matrix *a = matrix_new(size, size);
	matrix *b = matrix_new(size, size);
	matrix_rand(a);
	matrix_rand(b);

	clock_t start = clock(); 
	matrix *res = op(a, b);
	clock_t end = clock(); 

	double t = (double) (end - start) / CLOCKS_PER_SEC;
	printf("'%s' takes %lf seconds on a %dx%d matrix\n", name, t, size, size);

	matrix_free(a);
	matrix_free(b);
        matrix_free(res);
}

void test_sparse_unary(int size)
{
	matrix *a = matrix_new(size, size);
	matrix_zrand(a, size);

	clock_t start, end;
	double t;

	start = clock();
	smatrix_entry *sa = smatrix_new(a);
	end = clock();

	t = (double) (end - start) / CLOCKS_PER_SEC;
	printf("'smatrix_new' takes %lf seconds on a %dx%d sparse matrix\n", t, size, size);

	start = clock();
	smatrix_entry *sb = smatrix_trans(sa);
	end = clock();

	t = (double) (end - start) / CLOCKS_PER_SEC;
	printf("'smatrix_trans' takes %lf seconds on a %dx%d sparse matrix\n", t, size, size);

	matrix_free(a);
	smatrix_free(sa);
	smatrix_free(sb);
}

void test_sparse_binary(int size, matrix* (*op)(smatrix_entry*, smatrix_entry*), const char *name)
{
	matrix *a = matrix_new(size, size);
	matrix *b = matrix_new(size, size);
	matrix_zrand(a, size);
	matrix_zrand(b, size);

	smatrix_entry *sa = smatrix_new(a);
	smatrix_entry *sb = smatrix_new(b);

	clock_t start = clock();
	matrix *res = op(sa, sb);
	clock_t end = clock(); 

	double t = (double) (end - start) / CLOCKS_PER_SEC;
	printf("'%s' takes %lf seconds on a %dx%d sparse matrix\n", name, t, size, size);

	matrix_free(a);
	matrix_free(b);
	smatrix_free(sa);
	smatrix_free(sb);
        matrix_free(res);
}

int main()
{
	srand(time(0));

	int inputs[11] = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};

	for (int i = 0; i < 11; i++)
	{
		test_normal_binary(inputs[i], matrix_add, "matrix_add");
		test_normal_binary(inputs[i], matrix_sub, "matrix_sub");
		test_normal_binary(inputs[i], matrix_mult, "matrix_mult");
		test_normal_binary(inputs[i], matrix_div, "matrix_div");
		puts("");
	}

	for (int i = 0; i < 11; i++)
	{
		test_sparse_unary(inputs[i]);
		puts("");
	}

	for (int i = 0; i < 11; i++)
	{
		test_sparse_binary(inputs[i], smatrix_add, "smatrix_add");
		test_sparse_binary(inputs[i], smatrix_sub, "smatrix_sub");
		test_sparse_binary(inputs[i], smatrix_mult, "smatrix_mult");
		puts("");
	}

	return 0;
}

