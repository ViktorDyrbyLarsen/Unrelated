#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"

int axpy(const double alpha, const array_t *x, array_t *y);

int main(void)
{
    /* 
    This test program constructs "dynamic arrays" using automatic allocation. 
    The proper way of allocating dynamic arrays is to use dynamic memory 
    allocation to enable resizing of the arrays.    
    */
    double array1[10] = {1,2,3,4,5,6,7,8,9,10};
    double array2[10] = {1,1,1,1,1,1,1,1,1,1};
    array_t x = { .len = 10, .capacity = 10, .val = array1};
    array_t y = { .len = 4, .capacity = 10, .val = array2};

    // Check that axpy() returns 1 if arrays have different lengths
    if (axpy(2.0, &x, &y) != 1) {
        fprintf(stderr, "axpy() should return 1 if arrays have different lengths\n");
        return EXIT_FAILURE;
    }

    // Check that axpy() returns 1 if length is larger than capacity
    x.len = 11;
    if (axpy(2.0, &x, &y) != 1) {
        fprintf(stderr, "axpy() should return 1 if length is larger than capacity\n");
        return EXIT_FAILURE;
    }
    x.len = 10;
    y.len = 11;
    if (axpy(2.0, &x, &y) != 1) {
        fprintf(stderr, "axpy() should return 1 if length is larger than capacity\n");
        return EXIT_FAILURE;
    }

    // Check that axpy() returns 0 if arrays have same lengths
    y.len = 10;
    if (axpy(2.0, &x, &y) != 0) {
        fprintf(stderr, "axpy() should return 0 if arrays have same lengths\n");
        return EXIT_FAILURE;
    }
    // Check that computation is correct
    for (size_t i = 0; i < x.len; i++) {
        if (fabs(y.val[i] - (2*(i+1)+1)) > 1e-14) {
            fprintf(stderr, "axpy() should set y[i] += 2.0 * x[i]\n");
            return EXIT_FAILURE;
        }
    }

    // Check that axpy() returns 1 if one of the inputs is a NULL pointer
    if (axpy(2.0, NULL, &y) != 1 || axpy(2.0, &x, NULL) != 1) {
        fprintf(stderr, "axpy() should return 1 if one of the inputs is a NULL pointer\n");
        return EXIT_FAILURE;
    }

    printf("Test successful!\n");
    return EXIT_SUCCESS;
}
