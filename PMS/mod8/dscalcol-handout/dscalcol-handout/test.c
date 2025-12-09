#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array2d.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int dscalcol(double alpha, array2d_t *A, size_t k);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{

    int rc;
    array2d_t A = { 
        .shape =  {3,4}, 
        .val = (double []){1,2,3,4,5,6,7,8,9,10,11,12},
        .order = RowMajor
    };

    // Check error handling
    if (dscalcol(2.0, &A, 4) != 1) // k is out of bounds
    {
        printf("  ***Test failed. Unexpected return code when index is out of bounds.\n");
        return EXIT_FAILURE;
    }
    if (dscalcol(2.0, NULL, 1) != 1) // A is NULL
    {
        printf("  ***Test failed. Unexpected return code when A is NULL.\n");
        return EXIT_FAILURE;
    }
    
    // Test for RowMajor input: scale the second row by 2.0
    rc = dscalcol(2.0, &A, 1);
    if (rc != 0)
    {
        printf("  ***Test failed. Unexpected return code.\n");
        return EXIT_FAILURE;
    }

    double Ar_expected[] = {1,4,3,4,5,12,7,8,9,20,11,12};
    for (size_t i = 0; i < A.shape[0] * A.shape[1]; i++)
    {
        if (!isclose(A.val[i], Ar_expected[i], 1e-10, 1e-10))
        {
            printf("  ***Test failed. Unexpected result with RowMajor input.\n");
            return EXIT_FAILURE;
        }
    }
    dscalcol(0.5, &A, 1);  // Undo scaling

    // Test for ColMajor input: scale the last row by 2.0
    A.order = ColMajor;
    rc = dscalcol(2.0, &A, 2);
    if (rc != 0)
    {
        printf("  ***Test failed. Unexpected return code.\n");
        return EXIT_FAILURE;
    }

    double Ac_expected[] = {1,2,3,4,5,6,14,16,18,10,11,12};
    for (size_t i = 0; i < A.shape[0] * A.shape[1]; i++)
    {
        if (!isclose(A.val[i], Ac_expected[i], 1e-10, 1e-10))
        {
            printf("  ***Test failed. Unexpected result with ColMajor input.\n");
            //return EXIT_FAILURE;
        }
    }
    dscalcol(0.5, &A, 2);  // Undo scaling

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
