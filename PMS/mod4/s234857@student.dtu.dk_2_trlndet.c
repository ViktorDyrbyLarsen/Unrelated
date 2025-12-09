#include <stdlib.h>
#include <math.h>

double trlndet(int n, double * T) {
    if (!T) return NAN;
    double detT = 0;
    int sign = 1;

    for (int i = 0; i < n; ++i) {
        double a = T[i * n + i];

        if (!isnormal(a)) return NAN;

        if (a < 0.0) {
            sign = -sign;
            a = -a;              
        }
        detT += log(a);
    }
    if (sign < 0) return NAN;

    return detT;
}