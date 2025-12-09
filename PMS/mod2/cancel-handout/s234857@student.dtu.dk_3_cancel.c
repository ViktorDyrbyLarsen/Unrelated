#include <math.h>

/* Evaluates f(x) = (1-cos(x))/(x*x) */
double feval(double x) {
    if (x == 0) {
        return 0.5;
    }
    double result = 2*sin(x/2)*sin(x/2) / (x*x);
    if (isinf(x)) {
      return 0;  
    }

    else {
        return result;
    }
}
