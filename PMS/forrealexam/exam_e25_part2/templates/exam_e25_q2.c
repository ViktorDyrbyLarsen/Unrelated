// 02635 Final exam (E25)
// Template for part 2/2, Question 2

#include <stdlib.h>
#include <math.h>

double findterm(double x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x;

    double term = ((2*k - 1)*x*findterm(x,k-1) - (k - 1)*findterm(x,k-2)) / k;
    // term /= k;
    return term;
}

double legendreseries(double x, const double *c, int n) 
{
    if (!c || x > 1 || x < -1 || n < 0) return NAN;
    // double * terms = malloc(sizeof(double)*(n+1));
    double sum;
    for (int i = n; i >= 0; i--){
        sum += c[i]*findterm(x,n);
    }


    // free(terms);
    return sum;
}