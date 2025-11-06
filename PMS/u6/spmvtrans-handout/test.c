#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coo.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

void spmvtrans(const coo_t *A, const double *x, double *y);
int isclose(double a, double b, double rel_tol, double abs_tol);

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

    // Construct x and y
    double x[3] = {1,2,3};
    double y[4] = {-1,1,2,0};

    // Compute y = A*x
    printf("Testing spmvtrans() with valid inputs...\n");
    spmvtrans(&A, x, y);

    // Check result
    double yref[4] = {15,5,26,25};
    for (size_t i = 0; i < 4; i++)
    {
        if (!isclose(y[i], yref[i], 1e-8, 1e-8))
        {
            fprintf(stderr, "  ***Test failed. The result is incorrect.\n");
            return EXIT_FAILURE;
        }
    }

    // NULL test
    printf("Testing with NULL inputs...\n");
    printf("Testing with NULL inputs...\n");
    spmvtrans(&A, x, NULL); // This will result in a segfault if spmv() does not handle NULL input correctly.
    spmvtrans(&A, NULL, y); // This will result in a segfault if spmv() does not handle NULL input correctly.
    spmvtrans(NULL, x, y);  // This will result in a segfault if spmv() does not handle NULL input correctly.

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
