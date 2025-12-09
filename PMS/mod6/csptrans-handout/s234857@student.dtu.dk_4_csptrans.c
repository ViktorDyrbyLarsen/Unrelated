#include <stdlib.h>
#include "csp.h"

void csptrans(csp_t *A){
    if (!A) return;
    size_t shape0 = A->shape[0];
    
    A->shape[0] = A->shape[1];
    A->shape[1] = shape0;

    A->csx = (A->csx == CSC) ? CSR : CSC;
};
