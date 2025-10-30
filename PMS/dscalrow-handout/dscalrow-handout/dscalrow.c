#include <stdlib.h>
#include "array2d.h"

/* DSCAL (scale double array)                      */
void dscal_(
    const int * n,          /* length of array     */
    const double * a,       /* scalar a            */
    double * x,             /* array x             */
    const int * incx        /* array x, stride     */
);

/* Scale the k'th row of a two-dimensional array */
int dscalrow(double alpha, array2d_t *A, size_t k) {
    // Insert your code here
}

