#include <math.h>

/* Evaluates f(x) = log(n choose k) */
double logbinom(const unsigned int n, const unsigned int k){
    int nmk = n - k;
    

    if (n < k){
        return NAN;
    }

    return lgamma(n+1) - (lgamma(k+1) + lgamma(nmk+1));


}
