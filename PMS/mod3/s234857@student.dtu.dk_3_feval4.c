#include <math.h>

double feval(double x) {
    if (isnan(x)) {
        return NAN;
    }

    if (x == INFINITY) {
        return x;
    }
    if (x == 0) {
        return 1;
    }

    return (exp(x) * expm1(x)) / x;
}
