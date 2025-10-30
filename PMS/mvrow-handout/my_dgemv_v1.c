#include "my_dgemv_v1.h"

int my_dgemv_v1(
    double alpha,
    double beta,
    const array2d_t *A,
    const array_t *x,
    array_t *y
) {
    if (!A||!x||!y) return 1;
    if (A->shape[1] != x->len || A->shape[0] != y->len || isnan(alpha) || isnan(beta)) return 1;

    for (int i = 0; i < A->shape[0]; i++) {
        y->val[i] *= beta;
        for (int j = 0; j < A->shape[1]; j++) {
            if (isnan(A->val[i + j * A->shape[0]]) || isnan(x->val[j])) return 1;
            y->val[i] += alpha * A->val[j + i * A->shape[1]] * x->val[j];
        }
    }
    return 0;

}
