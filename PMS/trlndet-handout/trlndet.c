#include <stdlib.h>
#include <math.h>

double trlndet(int n, double * T) {
    if (!T) return NAN;
    double detT = 0;
    int sign = 1;

    for (int i = 0; i < n; i++) {
        if (T[i * n + i] == 0) return NAN;
        if (T[i * n + i] < 0) sign = -sign;
        
    }
    if (sign < 0) return NAN;
    for (int i = 0; i < n; i++) {
        detT += log(abs(T[i * n + i]));
    }
    return detT;
}