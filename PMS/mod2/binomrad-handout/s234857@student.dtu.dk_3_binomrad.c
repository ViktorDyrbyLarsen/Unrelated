#include <math.h>

/* Evaluates f(x) = sqrt(x*x+1) - 1 */
double feval(double x) {
    double r = hypot(x, 1.0); // Avoiding under- and overflow
    if (fabs(x) <= 1.0) { // Avoiding cancellation when |x| is small
        return (x * x) / (r + 1.0);
    } else { // Normal calculation otherwise 
        return r - 1.0;
    }
}