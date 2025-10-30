#include <stdlib.h>
#include <math.h>

double harmmean(int n, double *x, double *w) {
    if (!x || !w) return NAN;
    double topsum = 0.0;
    double botsum = 0.0;
    double xsum = 0.0; 
    for (int i = 0; i < n; i++) {
        if (x[i] <= 0 || w[i] <= 0) return NAN;
        topsum += w[i]; 
        botsum += w[i] / x[i];
        xsum += x[i];
    }
    return topsum / botsum;
}
