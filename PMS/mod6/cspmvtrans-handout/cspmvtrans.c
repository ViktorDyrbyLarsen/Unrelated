#include <stdlib.h>
#include "csp.h"

void cspmvtrans(const csp_t *A, const double *x, double *y) {
        if (!A || !x || !y) return;

    if (A->csx == CSC) {

        for (size_t i = 0; i < A->shape[1]; i++) {

            double Ax_i = 0;

            for (size_t j = A->ptr[i]; j < A->ptr[i+1]; j++) {

                Ax_i += A->val[j] * x[A->idx[j]];

            }

            y[i] += Ax_i;

        }
    }

    else if (A->csx == CSR) {

        for (size_t j = 0; j < A->shape[0]; ++j) {

            for (size_t i = A->ptr[j]; i < A->ptr[j+1]; i++) {

                y[A->idx[i]] += A->val[i] * x[j];
            }
        }
    }
}