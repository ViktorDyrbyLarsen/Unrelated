#include <stdlib.h>
#include "coo.h"

void sptrans(coo_t *A){
    if (!A || !A->rowidx || !A->colidx || !A->val) return;
    for (size_t i = 0; i < A->nnz; i++){
        size_t tmp = A->rowidx[i];
        A->rowidx[i] = A->colidx[i];
        A->colidx[i] = tmp;
        
    }
    size_t tmp_shape = A->shape[0];
    A->shape[0] = A->shape[1];
    A->shape[1] = tmp_shape;
};
