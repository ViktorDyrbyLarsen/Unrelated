#include <stdlib.h>
#include <math.h>

int dcemv(int n, double *x)
{
    if (!x || n <= 0) {
        return 1;
    }
    double mean = 0.0;
    for (int i = 0; i < n; i++) {
        if (isnan(x[i]) || isinf(x[i])) return 1;
        
        mean += x[i];
    }
    mean /= n;

    for (int i = 0; i < n; i++) {
        x[i] -= mean; 
    }

    return 0;

}