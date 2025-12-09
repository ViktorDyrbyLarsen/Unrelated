#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b));

double feval(double x);
int isclose(double a, double b, double rel_tol, double abs_tol);

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 3) {
        printf("Usage: %s x [yref]\n", argv[0]);
        return 1;
    }
    
    double x = atof(argv[1]);
    double y = feval(x);
    printf("  f(%.9g) = %.9g\n", x, y);

    if (argc == 3) {
        double yref = atof(argv[2]);
        if (isclose(y, yref, 1e-9, 0.0)) {
            fprintf(stderr,"Test passed.\n");
            return EXIT_SUCCESS;
        } 
        else {
            fprintf(stderr,"Test failed! Expected output: %.8g\n", yref);
            return EXIT_FAILURE;
        }
    }
    else {
        return EXIT_SUCCESS;
    }
}

int isclose(double a, double b, double rel_tol, double abs_tol)
{
    if (isfinite(a) && isfinite(b)) {
        // abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)
        double abs_a = fabs(a);
        double abs_b = fabs(b);    
        double abs_ab_max = MAX(abs_a, abs_b);
        return fabs(a-b) <= MAX(rel_tol*abs_ab_max, abs_tol);
    }
    else if (isinf(a) && isinf(b)) {
        return a == b;   // a and b have the same sign
    }
    else if (isnan(a) && isnan(b)) {
        return 1;        // a and b are both NaN
    }    
    else {
        return 0;
    }
}