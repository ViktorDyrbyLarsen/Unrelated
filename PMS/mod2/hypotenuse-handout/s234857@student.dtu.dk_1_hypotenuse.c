#include <math.h>

/* Evaluates f(x) = sqrt(x*x+y*y) */
double feval(double x, double y) {
    return hypot(x, y);
}
