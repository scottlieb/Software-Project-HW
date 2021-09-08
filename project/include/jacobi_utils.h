#ifndef PROJECT_JACOBI_UTILS_H
#define PROJECT_JACOBI_UTILS_H

#include "../include/matrix_utils.h"

/*Type 'ituple' is an integer tuple*/
typedef struct ituple {
	int i;
	int j;
} ituple;

/*Returns 'i', 'j'; indeces of largest off-center element in diagonal matrix.*/
ituple get_largest_off_i_j(matrix* mat);

/*Returns 'P'; transition matrix of A*/
matrix* get_P(matrix* A);

/*Returns A'; next iteration of A in Jacobi algorithm.*/
matrix* get_A_tag(matrix* A, matrix* P);

#endif