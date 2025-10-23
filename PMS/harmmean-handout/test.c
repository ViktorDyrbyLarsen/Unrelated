#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b));

double harmmean(int n, double *x, double *w);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{
    int n = 5;
    double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double w[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    double sol = harmmean(n, x, w);
    double solref = 3.0;
    if (!isclose(sol, solref, 1e-9, 0.0))
    {
        fprintf(stderr, "  ***Test failed. The result is incorrect.\n");
        return EXIT_FAILURE;
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
