// 02635 Final exam (E25)
// Template for part 2/2, Question 1

#include <stdlib.h>
#include <math.h>

double log1mexp(double x)
{
    if (isnan(x) || x<0) return NAN;
    if (x == 0) return -INFINITY;
    double result;
    if (x<1){
        result = log(expm1(x)) - x;
    }
    else {
        result = log(expm1(x)) - x;
        //result = log(1-exp(-x));
    }
    return result;
}
