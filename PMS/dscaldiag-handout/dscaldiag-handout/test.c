#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array2d.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int dscaldiag(double alpha, array2d_t *A);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{

    int rc;
    array2d_t A = { 
        .shape =  {4,3}, 
        .val = (double []){1,2,3,4,5,6,7,8,9,10,11,12},
        .order = RowMajor
    };

    // Check error handling
    if (dscaldiag(2.0, &A) != 1) // non-square matrix
    {
        printf("  ***Test failed. Unexpected return code when matrix is not square.\n");
        return EXIT_FAILURE;
    }
    if (dscaldiag(2.0, NULL) != 1) // A is NULL
    {
        printf("  ***Test failed. Unexpected return code when A is NULL.\n");
        return EXIT_FAILURE;
    }

    array2d_t B = { 
        .shape =  {4,4}, 
        .val = (double []){1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
        .order = RowMajor
    };
    
    // Test for RowMajor input: scale the second row by 2.0
    rc = dscaldiag(2.0, &B);
    if (rc != 0)
    {
        printf("  ***Test failed. Unexpected return code.\n");
        return EXIT_FAILURE;
    }
    double Br_expected[] = {2,2,3,4,5,12,7,8,9,10,22,12,13,14,15,32};
    for (size_t i = 0; i < B.shape[0] * B.shape[1]; i++)
    {
        if (!isclose(B.val[i], Br_expected[i], 1e-10, 1e-10))
        {
            printf("  ***Test failed. Unexpected result with RowMajor input.\n");
            return EXIT_FAILURE;
        }
    }
    dscaldiag(0.5, &B);  // Undo scaling

    // Test for ColMajor input: scale the last row by 2.0
    B.order = ColMajor;
    rc = dscaldiag(2.0, &B);
    if (rc != 0)
    {
        printf("  ***Test failed. Unexpected return code.\n");
        return EXIT_FAILURE;
    }
    double Bc_expected[] = {2,2,3,4,5,12,7,8,9,10,22,12,13,14,15,32};
    for (size_t i = 0; i < B.shape[0] * B.shape[1]; i++)
    {
        if (!isclose(B.val[i], Bc_expected[i], 1e-10, 1e-10))
        {
            printf("  ***Test failed. Unexpected result with ColMajor input.\n");
            return EXIT_FAILURE;
        }
    }
    dscaldiag(0.5, &B);  // Undo scaling

    printf("Tests successful!\n");
    return EXIT_SUCCESS;
}


int isclose(double a, double b, double rel_tol, double abs_tol)
{
    if (isfinite(a) && isfinite(b))
    {
        // abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)
        double abs_a = fabs(a);
        double abs_b = fabs(b);
        double abs_ab_max = MAX(abs_a, abs_b);
        return fabs(a - b) <= MAX(rel_tol * abs_ab_max, abs_tol);
    }
    else if (isinf(a) && isinf(b))
    {
        return a == b; // a and b have the same sign
    }
    else if (isnan(a) && isnan(b))
    {
        return 1; // a and b are both NaN
    }
    else
    {
        return 0;
    }
}
