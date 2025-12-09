#include <stdlib.h>
#include "csp.h"

void cspmv(const csp_t *A, const double *x, double *y) {
    if (!A || !x || !y) return;
    
    
    
    if (A->csx == CSR) {
        for (int i = 0; i < A->shape[0]; i++) {
            double Ax_i = 0;
            for (int j = A->ptr[i]; j < A->ptr[i+1]; j++) {
                Ax_i += A->val[j] * x[A->idx[j]];
            }
            
            y[i] += Ax_i;
        }
    }


    else if (A->csx == CSC) {
        for (int j = 0; j < A->shape[1]; ++j) {
            for (int i = A->ptr[j]; i < A->ptr[j+1]; i++) {
                y[A->idx[i]] += A->val[i] * x[j];
            }
    }
    // else if (A->csx == CSC) {
    //     for (int j = 0; j < A->ptr[A->shape[0]]; j++){
    //         for (int i = A->ptr[j]; j < A->ptr[j+1]; i++){
    //             y[A->idx[i]] += A->val[A->idx[i]];
    //         }
    //     }
    // }
    }
}