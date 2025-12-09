#include <stdlib.h>
#include <math.h>

int dhmsv(int n, double * a, double * b, double * x) {
    // null checks
    if (!a || !b || !x) return -1;

    
    for (int i = 0; i < n-1; i++) {
        if (a[i] == 0) return -1;
        x[i] = a[i];
        x[n] -= (b[i]*x[i]);
    }
    x[n] += a[n]*x[n];

    return 0;
}
