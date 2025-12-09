#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int lsegrad(double * x, int n);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{
    int n = 5;
    double x[5] = {.44702441, -0.39155831,  0.85569149, -1.18841173,  0.29167892};
    double g[5] = {0.2507447 , 0.10840265, 0.3773233 , 0.04886196, 0.21466739};

    printf("Testing lsegrad() with valid inputs...\n");
    int rc = lsegrad(x,n);

    // Check result
    if (rc != 0) {
        fprintf(stderr, "Unexpected return value.\n");
        return EXIT_FAILURE;
    }
    for (int i=0;i<n;i++) {
        if (!isclose(x[i], g[i], 1e-6, 1e-6))
        {
            fprintf(stderr, "  ***Test failed. The result is incorrect.\n");
            return EXIT_FAILURE;
        }
    }
    
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
