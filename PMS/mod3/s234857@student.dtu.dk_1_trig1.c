#include <math.h>

/* Evaluates f(x) = (1-cos(x))/sin(x) */
double feval(double x) {
    
    if (isnan(x) || isinf(x)) return NAN;
    return tan(x/2);
}
