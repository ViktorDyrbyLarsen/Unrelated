// 02635 Final exam (E24)
// Template for part 2/2, Question 1

#include <stdlib.h>
#include <math.h>
// Computes 
double feval(double x)
{
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
