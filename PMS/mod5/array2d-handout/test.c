#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"
#include "array2d.h"

int array2d_scale_rows(array_t *alpha, array2d_t *A);

int main(void)
{
    /* 
    This test program constructs "dynamic arrays" using automatic allocation. 
    The proper way of allocating dynamic arrays is to use dynamic memory 
    allocation to enable resizing of the arrays.    
    */
    double array1[4] = {-1,-2,-3,-4};
    array_t alpha = { .len = 4, .capacity = 4, .val = array1};

    // Construct array2d_t objects (Ar is RowMajor, Ac is ColMajor)
    double array_rm[4][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    double array_cm[3][4] = {{1,4,7,10},{2,5,8,11},{3,6,9,12}};
    double ans[4][3]    = {{-1,-2,-3},{-8,-10,-12},{-21,-24,-27},{-40,-44,-48}};
    array2d_t Ar = { .shape = {4,3}, .order = RowMajor, .val = &array_rm[0][0]};
    array2d_t Ac = { .shape = {4,3}, .order = ColMajor, .val = &array_cm[0][0]};

    // Check that array2d_scale_rows() returns 1 if the length of alpha does not match the number of rows in A
    alpha.len = 3; // Temporarily change alpha.len
    if (array2d_scale_rows(&alpha, &Ar) != 1) {
        fprintf(stderr, "array2d_scale_rows(alpha, A) should return 1 if dimensions do not match\n");
        return EXIT_FAILURE;
    }
    alpha.len = 4; // Restore alpha.len

    // Check that array2d_scale_rows() returns 1 if it received a NULL pointer
    if (array2d_scale_rows(NULL, &Ar) != 1) {
        fprintf(stderr, "array2d_scale_rows(alpha, A) should return 1 if alpha is NULL\n");
        return EXIT_FAILURE;
    }
    if (array2d_scale_rows(&alpha, NULL) != 1) {
        fprintf(stderr, "array2d_scale_rows(alpha, A) should return 1 if A is NULL\n");
        return EXIT_FAILURE;
    }

    // Check that array2d_scale_rows() returns 0 if dimensions match
    if (array2d_scale_rows(&alpha, &Ar) != 0) {
        fprintf(stderr, "array2d_scale_rows(alpha, A) should return 0 if inputs are valid\n");
        return EXIT_FAILURE;
    }
    if (array2d_scale_rows(&alpha, &Ac) != 0) {
        fprintf(stderr, "array2d_scale_rows(alpha, A) should return 0 if inputs are valid\n");
        return EXIT_FAILURE;
    }

    // Check that computation is correct
    size_t m = Ar.shape[0], n = Ar.shape[1];
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {            
            if (fabs(Ar.val[i*n+j] - ans[i][j]) > 1e-14) {
                fprintf(stderr, "array2d_scale_rows(alpha, A) failed for RowMajor input\n");
                return EXIT_FAILURE;
            }
            if (fabs(Ac.val[i+j*m] - ans[i][j]) > 1e-14) {
                fprintf(stderr, "array2d_scale_rows(alpha, A) failed for ColMajor input\n");
                return EXIT_FAILURE;
            }
        }
    }

    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
