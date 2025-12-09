#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csp.h"

void csptrans(csp_t *A);

int main(void)
{
    /* 
    This test program constructs a csp_t using automatic allocation. 
    This is done for test purposes only. 
    */

    // Construct csp_t variable A
    size_t ptr[4] = {0,2,3,5};
    size_t idx[6] = {1,2,0,2,3};
    double val[6] = {1,2,3,4,5};
    csp_t A = {.shape = {3,4}, .csx = CSR, .ptr = ptr, .idx = idx, .val = val};

    // Call csptrans
    csptrans(&A);

    // Test
    if(A.csx == CSR){

        // Construct correct triplets for comparison
        size_t trans_ptr[4] = {0,1,3,5};
        size_t trans_idx[6] = {1,0,0,2,2};
        double trans_val[6] = {3,1,2,4,5};

        // Check dimensions
        if (A.shape[0] != 4 || A.shape[1] != 3)
        {
            printf("  ***Test failed: wrong dimensions\n");
            return EXIT_FAILURE;
        }

        // Check ptr
        for (size_t i = 0; i < 4; i++)
        {
            if (A.ptr[i] != trans_ptr[i])
            {
                printf("  ***Test failed: wrong row indices\n");
                return EXIT_FAILURE;
            }
        }

        // Check indices
        for (size_t i = 0; i < 5; i++)
        {
            if (A.idx[i] != trans_idx[i])
            {
                printf("  ***Test failed: wrong row indices\n");
                return EXIT_FAILURE;
            }
        }

        // Check values
        for (size_t i = 0; i < 5; i++)
        {
            if (A.val[i] != trans_val[i])
            {
                printf("  ***Test failed: wrong values\n");
                return EXIT_FAILURE;
            }
        }

    }
    else{

        // Construct correct triplets for comparison
        size_t trans_ptr[4] = {0,2,3,5};
        size_t trans_idx[6] = {1,2,0,2,3};
        double trans_val[6] = {1,2,3,4,5};

        // Check dimensions
        if (A.shape[0] != 4 || A.shape[1] != 3)
        {
            printf("  ***Test failed: wrong dimensions\n");
            return EXIT_FAILURE;
        }

        // Check ptr
        for (size_t i = 0; i < 4; i++)
        {
            if (A.ptr[i] != trans_ptr[i])
            {
                printf("  ***Test failed: wrong row indices\n");
                return EXIT_FAILURE;
            }
        }

        // Check indices
        for (size_t i = 0; i < 5; i++)
        {
            if (A.idx[i] != trans_idx[i])
            {
                printf("  ***Test failed: wrong row indices\n");
                return EXIT_FAILURE;
            }
        }

        // Check values
        for (size_t i = 0; i < 5; i++)
        {
            if (A.val[i] != trans_val[i])
            {
                printf("  ***Test failed: wrong values\n");
                return EXIT_FAILURE;
            }
        }
    }


    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
