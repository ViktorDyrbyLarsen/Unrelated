#include "my_dgemv_v1.h"
#include <math.h>
#include <stddef.h>

int my_dgemv_v1(
    double alpha,
    double beta,
    const array2d_t *A,
    const array_t *x,
    array_t *y
) {
    if (!A || !x || !y) return 1;
    size_t m = A->shape[0];
    size_t n = A->shape[1];

    if (n != x->len || m != y->len || isnan(alpha) || isnan(beta)) return 1;

    for (size_t i = 0; i < m; ++i) {
        y->val[i] *= beta;
        for (size_t j = 0; j < n; ++j) {
            double aij = A->val[i * n + j];  // row-major
            if (isnan(aij) || isnan(x->val[j])) return 1;
            y->val[i] += alpha * aij * x->val[j];
        }
    }
    return 0;
}
