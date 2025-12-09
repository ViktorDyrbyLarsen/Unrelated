#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dcemv(int n, double *x);

int main(void)
{

    double x[] = {1.0, 3.0, 0.0, 4.0, -1.0, 5.0};    
    int n = sizeof(x)/sizeof(x[0]);

    if (dcemv(-1, x) != 1) {
        fprintf(stderr, "Negative size test failed!\n");
        return EXIT_FAILURE;
    }

    if (dcemv(n, NULL) != 1) {
        fprintf(stderr, "NULL pointer test failed!\n");
        return EXIT_FAILURE;
    }

    if (dcemv(n, x) != 0) {
        fprintf(stderr, "Test failed! Expected output: 0\n");
        return EXIT_FAILURE;
    } else {
        for (int i = 0; i < n; i++) {
            printf("%f ", x[i]);
        }
        printf("Test passed!\n");
    }

    return EXIT_SUCCESS;
}
