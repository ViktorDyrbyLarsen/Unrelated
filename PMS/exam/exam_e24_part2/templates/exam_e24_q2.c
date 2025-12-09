// 02635 Final exam (E24)
// Template for part 2/2, Question 2

#include <stdlib.h>
#include <math.h>

double chebseries(double x, const double *c, int n)
{
    if (!c || n < 0){
        return NAN;
    }

    if (x<-1 || x >1) return NAN;

    double result = chebseries(x,c,n-2) - chebseries(x,c,n-1);

    return result;


    if (n == 0) return c[0];
    if (n == 1) return c[0] * c[1]*x;
    
    double *terms = malloc((n+1)*sizeof(double));
    double sum = 0;

    terms[0] = c[0];
    terms[1] = c[0] * c[1]*x;


    for (int i = 2; i <= n; i++){
        terms[i] = 2*x*terms[i-1] - terms[i-2];
        sum += terms[i]*c[i];
    }

    free(terms);

    return sum;
}