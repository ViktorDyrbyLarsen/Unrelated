#include <stdlib.h>
#include "array2d.h"

/* DSCAL (scale double array)                      */
void dscal_(
    const int * n,          /* length of array     */
    const double * a,       /* scalar a            */
    double * x,             /* array x             */
    const int * incx        /* array x, stride     */
);

/* Scale the diagonal of a two-dimensional array */
int dscaldiag(double alpha, array2d_t *A) {
    // Insert your code here
}

