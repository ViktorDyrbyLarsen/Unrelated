#include <math.h>

/* Evaluates f(x) = exp(x) - exp(-x) */
double feval(double x) {
    return 2*sinh(x);
}
