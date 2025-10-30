#include "my_dgemv_v2.h"
#include <math.h>

int my_dgemv_v2(
    double alpha,
    double beta,
    const array2d_t *A,
    const array_t *x,
    array_t *y
) {
    if (!A||!x||!y) return 1;
    int m = A->shape[0]; // rows
    int n = A->shape[1]; // columns
    
    if (n != x->len || m != y->len || isnan(alpha) || isnan(beta)) return 1;
    
    for (size_t i = 0; i < y->len; i++) {
        if(isnan(y->val[i])) return 1;
        y->val[i] *= beta;
    }
    
    for (size_t col = 0; col < n; col++) {
        for (size_t row = 0; row < m; row++) {
            if (isnan(A->val[row + col * m]) || isnan(x->val[col])) return 1;
            y->val[row] += alpha * A->val[row + col * m] * x->val[col];
        }
    }
    return 0;

}
