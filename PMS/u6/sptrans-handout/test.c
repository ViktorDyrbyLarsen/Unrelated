#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coo.h"

void sptrans(coo_t *A);

int main(void)
{
    /* 
    This test program constructs a coo_t using automatic allocation. 
    This is done for test purposes only. 
    */

    // Construct coo_t variable A
    size_t row[7] = {0,2,1,1,2,0,2};
    size_t col[7] = {0,0,1,2,2,3,3};
    double val[7] = {1,5,2,3,6,4,7};
    coo_t A = { .shape = {3,4}, .nnz = 7, .capacity = 7, .rowidx = row, .colidx = col, .val = val};

    // Call sptrans
    sptrans(&A);

    // Construct correct triplets for comparison
    size_t trans_col[7] = {0,2,1,1,2,0,2};
    size_t trans_row[7] = {0,0,1,2,2,3,3};
    double trans_val[7] = {1,5,2,3,6,4,7};

    // Check dimensions
    if (A.shape[0] != 4 || A.shape[1] != 3)
    {
        printf("  ***Test failed: wrong dimensions\n");
        return EXIT_FAILURE;
    }

    // Check nnz
    if (A.nnz != 7)
    {
        printf("  ***Test failed: wrong number of nonzeros\n");
        return EXIT_FAILURE;
    }

    // Check rowidx
    for (size_t i = 0; i < A.nnz; i++)
    {
        if (A.rowidx[i] != trans_row[i])
        {
            printf("  ***Test failed: wrong row indices\n");
            return EXIT_FAILURE;
        }
    }

    // Check colidx
    for (size_t i=0;i < A.nnz; i++)
    {
        if (A.colidx[i] != trans_col[i])
        {
            printf("  ***Test failed: wrong column indices\n");
            return EXIT_FAILURE;
        }
    }

    // Check values
    for (size_t i=0;i < A.nnz; i++) {
        if (A.val[i] != trans_val[i])
        {
            printf("  ***Test failed: wrong values\n");
            return EXIT_FAILURE;
        }
    }

    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
