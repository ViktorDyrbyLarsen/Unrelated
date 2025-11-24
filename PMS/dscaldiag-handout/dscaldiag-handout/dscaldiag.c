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
    if (!A || !A->val || A->shape[1] != A->shape[0]) return 1;

    const int n = A->shape[0]; // Dimension of square matrix
    const int stride = n + 1;

    dscal_(&n, &alpha, A->val, &stride);

    return 0;
}

