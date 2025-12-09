#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_dgemv_v2.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b));

int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{
    /*
    For test purposes only.
    */

    // Construct array2d_t variable A
    double valA[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    array2d_t A = {.shape = {3, 4}, .order = RowMajor, .val = valA};

    //double valA[12] = {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12};
    //array2d_t A = {.shape = {3, 4}, .order = ColMajor, .val = valA};

    // Construct array_t variable x
    double valx[4] = {1, 2, 3, 4};
    array_t x = {.len = 4, .capacity = 4, .val = valx};

    // Construct array_t variable y
    double valy[3] = {5, 6, 7};
    array_t y = {.len = 3, .capacity = 3, .val = valy};

    // Compute y = A*x
    printf("Testing my_dgemv_v2() with valid inputs...\n");
    if (my_dgemv_v2(2.0, 3.0, &A, &x, &y) != 0)
    {
        fprintf(stderr, "  ***Test failed. Unexpected return value.\n");
        return EXIT_FAILURE;
    }

    double yref[3] = {75.0, 158.0, 241.0};
    for (size_t i = 0; i < 3; i++)
    {
        if (!isclose(y.val[i], yref[i], 1e-8, 1e-8))
        {
            fprintf(stderr, "  ***Test failed. The result is incorrect.\n");
            return EXIT_FAILURE;
        }
    }

    printf("Testing my_dgemv_v2() with invalid inputs...\n");
    if (my_dgemv_v2(2.0, 3.0, NULL, &x, &y)!=1  ||  my_dgemv_v2(2.0, 3.0, &A, NULL, &y)!=1  ||  my_dgemv_v2(2.0, 3.0, &A, &x, NULL)!=1 ) {
        fprintf(stderr, "  ***Test failed.\n");
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
