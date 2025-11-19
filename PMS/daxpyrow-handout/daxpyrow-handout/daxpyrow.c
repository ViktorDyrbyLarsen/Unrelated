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

/* Adds alpha times row i to row j */
int daxpyrow(double alpha, array2d_t *A, size_t i, size_t j) {
    if (!A || i == j || i >= A->shape[0] || j >= A->shape[0]) return 1;

    const int n = A->shape[1];
    const int stride = A->order == RowMajor ? 1 : A->shape[0];
    daxpy_(
        &n, // column length
        &alpha, // scalar alpha
        A->order == RowMajor ? &A->val[A->shape[1] * i] : &A->val[i], // x start
        &stride, // stride
        A->order == RowMajor ? &A->val[A->shape[1] * j] : &A->val[j], // y start
        &stride  // stride 
    );
    
    return 0;
}