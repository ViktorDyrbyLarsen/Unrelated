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
    if (!A || i == j || i > A->shape[0] || j > A->shape[0]) return 1;

    const int n = A->shape[0];
    const int stride = A->order == RowMajor ? A->shape[1] : 1;
    daxpy_(
        &n, // column length
        &alpha, // scalar alpha
        A->order == RowMajor ? &A->val[i] : &A->val[A->shape[0] * i], // x start
        &stride, // stride
        A->order == RowMajor ? &A->val[j] : &A->val[A->shape[0] * j], // y start
        &stride  // stride 
    );
    
    return 0;
}

