#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int dhmsv(int n, double * a, double * b, double * x);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{
    int n = 5;
    double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double b[4] = {6.0, 7.0, 8.0, 9.0};
    double x[5] = {10.0, 11.0, 12.0, 13.0, 14.0};

    printf("Testing dhmsv() with valid inputs...\n");
    int rc = dhmsv(n, a, b, x);

    // Check result
    if (rc != 0)
    {
        fprintf(stderr, "  ***Test failed. Incorrect return value.\n");
        return EXIT_FAILURE;
    }

    double xref[5] = {10.0, 5.5, 4.0, 3.25, -29.15};
    for (size_t i = 0; i < 5; i++)
    {
        if (!isclose(x[i], xref[i], 1e-8, 1e-8))
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
