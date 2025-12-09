#include "carray2d.h"

int carray2d_add_diag(const double alpha, carray2d_t *A) {
    if (!A) {
        return 1;
    }
    if (A->shape[0] != A->shape[1]) {
        return 1;
    }
    for (size_t i = 0; i < A->shape[0]; i++) {
        A->val[i][i] += alpha;
    }
    return 0;
}