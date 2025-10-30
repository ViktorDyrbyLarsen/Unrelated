#include <stdlib.h>
#include "array2d.h"

/* DAXPY (double a x plus y)                          */
void daxpy_(
    const int * n,        /* length of arrays x and y */
    const double * a,     /* scalar a                 */
    const double * x,     /* array x                  */
    const int * incx,     /* array x, stride          */
    double * y,           /* array y                  */
    const int * incy      /* array y, stride          */
);

/* Adds alpha times column i to column j */
int daxpycol(double alpha, array2d_t *A, size_t i, size_t j) {
    // Insert your code here
}

