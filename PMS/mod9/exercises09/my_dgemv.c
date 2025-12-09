#include "msptools.h"

int
my_dgemv(double alpha,
	  double beta,
	  const array2d_t * A, 
	  const array_t * x, 
	  array_t * y) {

    if (!A || !x || !y)
	return 1;

    if (A->shape[1] != x->len || A->shape[0] != y->len)
	return 1;

	/* Insert your code here */

    return 0;
}
