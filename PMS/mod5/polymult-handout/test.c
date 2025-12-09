#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poly.h"

poly_t *polymul(const poly_t *p1, const poly_t *p2);

int main(void)
{

    // Create two polynomials
    double coef1[3] = {1,2,3};
    double coef2[4] = {-2,6,1,2};
    poly_t p1 = { .deg = 2, .coef = coef1 };
    poly_t p2 = { .deg = 3, .coef = coef2 };

    // Check that polymul() returns NULL if p1 and/or p2 is NULL
    if (polymul(NULL, &p2) != NULL || polymul(&p1, NULL) != NULL) {
        fprintf(stderr, "  ***Test failed. polymul() should return NULL if p1 or p2 is NULL\n");
        return EXIT_FAILURE;
    }

    // Check that polynomial multiplication is correct
    poly_t *p = polymul(&p1, &p2);
    if (p == NULL) {
        fprintf(stderr, "  ***Test failed. polymul() should not return NULL if p1 and p2 are not NULL\n");
        return EXIT_FAILURE;
    }
    if (p->deg != 5) {
        fprintf(stderr, " ***Test failed. Expected a polynomial of degree 5.\n");
        return EXIT_FAILURE;
    }
    double coef[6] = {-2,2,7,22,7,6}; // expected coefficients
    for (int i = 0; i < 6; i++) {
        if (fabs(p->coef[i] - coef[i]) > 1e-6) {
            fprintf(stderr, "  ***Test failed. Polynomial multiplication is incorrect.\n");
            return EXIT_FAILURE;
        }
    }
    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
