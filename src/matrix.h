#ifndef __MATRIX_H
#define __MATRIX_H

int** matrix_new(int, int);
void matrix_free(int**, int);
void matrix_rand(int**, int, int);
int matrix_nzcnt(int**, int, int);
void matrix_add(int**, int**, int**, int, int);
void matrix_sub(int**, int**, int**, int, int);
void matrix_mult(int**, int**, int**, int, int, int);
void matrix_div(int**, int**, int**, int, int);
void matrix_print(int **, int, int);

#endif
