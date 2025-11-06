#ifndef MY_DGEMV_H
#define MY_DGEMV_H

#include "msptools.h"

int my_dgemv(double alpha,
             double beta,
	     const array2d_t * A,
	     const array_t * x,
	     array_t * y);

#endif
