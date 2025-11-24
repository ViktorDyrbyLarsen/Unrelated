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
    if (!A || k >= A->shape[0]) return 1;

    const int rows = A->shape[0];
    const int cols = A->shape[1];
    
    if (A->order == RowMajor) {
        const int stride = 1;
        cblas_dscal(cols, alpha, &A->val[k*cols], stride);
    }
    else { // (if ColMajor)
        const int stride = rows;
        cblas_dscal(cols, alpha, &A->val[k], stride);
    }

    return 0;
}

