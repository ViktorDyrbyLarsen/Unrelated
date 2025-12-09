#include "array2d.h"
#include "array.h"

int array2d_scale_rows(array_t *alpha, array2d_t *A){
    if (!alpha || !A){
        return 1;
    }
    
    if (alpha->len != A->shape[0]){
        return 1;
    }
    
    for (int i = 0; i < alpha->len; i++){
        for (int j = 0; j < A->shape[1]; j++){
            if (A->order == RowMajor){
                A->val[i * A->shape[1] + j] *= alpha->val[i];
            } else {
                A->val[j * A->shape[0] + i] *= alpha->val[i];
            }
        }
    }

    return 0;
}
