#include "array.h"

int axpy(const double alpha, const array_t *x, array_t *y)
{
    // NULL pointer checks
    if (!x || !y) {
        return 1;
    }
    // Check whether x and y have equal length
    if (x->len != y->len) {
        return 1;
    }
    
    for (size_t i = 0; i < x->len; i++) {
        y->val[i] += alpha * x->val[i];
    }
    return 0;
}
