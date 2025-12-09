#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array2d.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define RMval(A,i,j)  ((A).val[i*(A).shape[1]+j])
#define CMval(A,i,j)  ((A).val[j*(A).shape[0]+i])

int dtrsvsolve(array2d_t *M, double *b);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(void)
{

    array2d_t Mr = {
        .shape = {6,6},
        .order = RowMajor,
        .val = (double []){ 6.00,  3.00,  2.00,  0.00,  2.00,  1.00,
                            0.17,  4.50,  0.67, -1.00,  1.70,  4.80,
                            0.00, -0.22,  5.10, -0.22,  6.40,  2.10,
                            0.17, -0.11, -0.24, -2.20, -0.59,  6.90,
                            0.83, -0.78,  0.36,  0.78,  3.80, -4.20,
                           -0.33, -0.00,  0.52, -0.51, -0.51,  1.70}
    };
    array2d_t Mc = {
        .shape = {6,6},
        .order = ColMajor,
        .val = (double []){0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
    };
    double b1[] = {1, 2, 3, 4, 5, 6};
    double b2[] = {1, 2, 3, 4, 5, 6};
    double xref[] = {1.497280524366798, -2.810817850889563, -6.856968670462646, 10.007475638577095, 4.924135722873066, 4.314436301647060};

    for (size_t i=0;i<6;i++) {
        for (size_t j=0;j<6;j++) {
            CMval(Mc,i,j) = RMval(Mr,i,j);
        }
    }

    // Test with ColMajor input
    printf("Testing with ColMajor input..\n");
    if (dtrsvsolve(&Mc, b2) != 0) {
        fprintf(stderr, "  ***Test failed. Unexpected return value.\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < Mc.shape[0]; i++)
    {
        if (!isclose(b2[i], xref[i], 1e-8, 1e-8))
        {
            fprintf(stderr, "  ***Test failed. Unexpected result.\n");            
            return EXIT_FAILURE;
        }
    }

    // Test with RowMajor input
    printf("Testing with RowMajor input..\n");
    if (dtrsvsolve(&Mr, b1) != 0) {
        fprintf(stderr, "  ***Test failed. Unexpected return value.\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < Mr.shape[0]; i++)
    {
        if (!isclose(b1[i], xref[i], 1e-8, 1e-8))
        {
            fprintf(stderr, "  ***Test failed. Unexpected result.\n");            
            return EXIT_FAILURE;
        }
    }

    // Test with invalid inputs
    printf("Testing with invalid inputs..\n");
    if (dtrsvsolve(&Mr,NULL) != 1) {
        fprintf(stderr, "  ***Test failed. Unexpected return value when b is NULL.\n");
        return EXIT_FAILURE;
    }
    if (dtrsvsolve(NULL,b1) != 1) {
        fprintf(stderr, "  ***Test failed. Unexpected return value when M is NULL.\n");
        return EXIT_FAILURE;
    }
    Mr.shape[0] -= 1;
    if (dtrsvsolve(&Mr,b1) != 1) {
        fprintf(stderr, "  ***Test failed. Unexpected return value when M is nonsquare.\n");
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
