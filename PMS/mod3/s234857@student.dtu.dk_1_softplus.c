#include <math.h>

/* softplus: evaluates the function f(x) = log(1+exp(x)) */
double feval(double x) {
    if (isnan(x)) return NAN;  
    if (x < 1e-2) return log1p(exp(x));
    return x + log(1 + exp(-x));
}
