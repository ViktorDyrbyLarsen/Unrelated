#include "my_dgemv_v2.h"
#include <math.h>
#include <stddef.h>

int my_dgemv_v2(
    double alpha,
    double beta,
    const array2d_t *A,
    const array_t *x,
    array_t *y
) {
    // Null-pointer check
    if (!A || !x || !y) return 1;

    // m = rows, n = columns
    size_t m = A->shape[0];
    size_t n = A->shape[1];

    // Dimension + scalar validity checks
    if (n != x->len || m != y->len || isnan(alpha) || isnan(beta)) return 1;

    // Scale y by beta, but fail if y already contains NaNs
    for (size_t i = 0; i < m; ++i) {
        if (isnan(y->val[i])) return 1;
        y->val[i] *= beta;
    }

    // Column-wise access: outer loop over columns j, inner over rows i
    for (size_t j = 0; j < n; ++j) {
        double xj = x->val[j];
        if (isnan(xj)) return 1;

        for (size_t i = 0; i < m; ++i) {
            // Column-major indexing: A(i,j) = A->val[i + j * m]
            double aij = A->val[i + j * m];
            if (isnan(aij)) return 1;

            y->val[i] += alpha * aij * xj;
        }
    }

    return 0;
}
