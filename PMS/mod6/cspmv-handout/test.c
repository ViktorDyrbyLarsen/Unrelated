#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "csp.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

void cspmv(const csp_t *A, const double *x, double *y);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{
    /* 
    This test program constructs a csp_t using automatic allocation. 
    This is done for test purposes only. 
    */

    // Construct csp_t variable A
    size_t ptr[4] = {0,2,3,6};
    size_t idx[6] = {0,3,1,0,2,3};
    double val[6] = {1,4,2,5,3,2};
    csp_t A = {.shape = {3,4}, .csx = CSR, .ptr = ptr, .idx = idx, .val = val};

    // Construct x and y
    double x[4] = {1,2,3,4};
    double y[3] = {3,2,-1};

    // Compute y = A*x
    printf("Testing cspmv() with valid inputs...\n");
    cspmv(&A, x, y);

    // Check result
    double yref[3] = {20,6,21};
    for (size_t i = 0; i < 3; i++)
    {
        if (!isclose(y[i], yref[i], 1e-8, 1e-8))
        {
            fprintf(stderr, "  ***Test failed. The result is incorrect.\n");
            return EXIT_FAILURE;
        }
    }

    // NULL tests: these may result in a segfault if cspmv() does not handle NULL inputs correctly.
    printf("Testing with NULL inputs...\n");
    cspmv(&A, x, NULL);
    cspmv(&A, NULL, y);
    cspmv(NULL, x, y);
    
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
