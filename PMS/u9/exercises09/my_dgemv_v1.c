#include "my_dgemv.h"

int
my_dgemv_v1(double alpha,
	     double beta,
	     const array2d_t * A, 
	     const array_t * x, 
	     array_t * y) {

    if (!A || !x || !y)
	return 1;

    if (A->shape[1] != x->len || A->shape[0] != y->len)
	return 1;

    size_t m = A->shape[0];
    size_t n = A->shape[1];
    double *px = x->val;
    double *py = y->val;

    if (A->order == RowMajor) {
	for (size_t i = 0; i < m; i++) {
	    py[i] *= beta;
	    double *pA = A->val + i * n;
	    double sum = 0.0;

	    for (size_t j = 0; j < n; j++) {
		sum += alpha * pA[j] * px[j];	// stride 1
	    }
	    py[i] += sum;
	}
    }
    else {
	for (size_t i = 0; i < m; i++) {
	    py[i] *= beta;
	    double *pA = A->val + i;
	    double sum = 0.0;

	    for (size_t j = 0; j < n; j++) {
		sum += alpha * pA[m * j] * px[j];	// stride m
	    }
	    py[i] += sum;
	}
    }
    return 0;
}
