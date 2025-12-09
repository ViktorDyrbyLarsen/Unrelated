#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "carray2d.h"

int carray2d_add_diag(const double alpha, carray2d_t *A);

int main(void)
{
    // Construct carray2d_t object
    carray2d_t A = { .shape = {4,4}, .val = NULL };
    A.val = malloc(A.shape[0] * sizeof(*(A.val)));
    A.val[0] = malloc(A.shape[0] * A.shape[1] * sizeof(*(A.val[0])));
    if (A.val == NULL || A.val[0] == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 1; i < A.shape[0]; i++) {
        A.val[i] = A.val[0] + i * A.shape[1];
    }
    // Initialize A.val
    for (size_t i=0; i < A.shape[0]; i++) {
        for (size_t j=0; j < A.shape[1]; j++) {
            A.val[i][j] = i * A.shape[1] + j;
        }
    }   

    // Check that carray2d_add_diag() returns 1 if it received a NULL pointer
    if (carray2d_add_diag(1.0, NULL) != 1) {
        fprintf(stderr, "  ***Test failed. Unexpected return value when input is NULL.\n");
        return EXIT_FAILURE;
    }

    // Check that carray2d_add_diag() returns 1 if dimensions don't match
    A.shape[0] = 3; // Temporarily change A.shape[0] to 3
    if (carray2d_add_diag(1.0, &A) != 1) {
        fprintf(stderr, "  ***Test failed. Unexpected return value when A is not square.\n");
        return EXIT_FAILURE;
    }
    A.shape[0] = 4; // Restore A.shape[0]

    // Check that carray2d_add_diag() returns 0 if dimensions match 
    if (carray2d_add_diag(1.0, &A) != 0) {
        fprintf(stderr, "  ***Test failed. Expected return value 0.\n");
        return EXIT_FAILURE;
    }

    // Check that computation is correct
    for (size_t i=0; i < A.shape[0]; i++) {
        if (fabs(A.val[i][i] - (i * A.shape[1] + i + 1)) > 1e-15) {
            fprintf(stderr, "  ***Test failed. Expected A.val[%zu][%zu] = %f, got %f.\n", i, i, (double) i * A.shape[1] + i + 1, A.val[i][i]);
            return EXIT_FAILURE;
        }
    }

    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
