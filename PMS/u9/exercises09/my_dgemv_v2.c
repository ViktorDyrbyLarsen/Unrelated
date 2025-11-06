#include "my_dgemv.h"

int
my_dgemv_v2(double alpha,
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

    for (size_t i = 0; i < m; i++)
	py[i] *= beta;

    if (A->order == RowMajor) {
	for (size_t j = 0; j < n; j++) {
	    double *pA = A->val + j;

	    for (size_t i = 0; i < m; i++) {
		py[i] += alpha * pA[i * n] * px[j];	// stride n
	    }
	}
    }
    else {
	for (size_t j = 0; j < n; j++) {
	    double *pA = A->val + j * m;

	    for (size_t i = 0; i < m; i++) {
		py[i] += alpha * pA[i] * px[j];	// stride 1
	    }
	}
    }
    return 0;
}
