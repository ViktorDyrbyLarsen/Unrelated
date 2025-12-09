#include <stdlib.h>
#include "coo.h"

void spmv(const coo_t *A, const double *x, double *y) {
    // Null pointer checks
    if (!A || !A->rowidx || !A->colidx || !A->val || !x || !y) return;

    for (size_t i = 0; i < A->nnz; i++) {
        y[A->rowidx[i]] += A->val[i] * x[A->colidx[i]];   
    }
}