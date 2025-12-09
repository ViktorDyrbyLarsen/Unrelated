#include <stdlib.h>
#include <math.h>

double lse(const double *x, int n)
{
    if (!x || n < 0) return NAN;
    
    double sum = 0;
    double max = x[0];
    int max_idx = 0;

    for (int i = 1; i < n; i++){
        if (x[i] > max){
            max = x[i];
            max_idx = i;
        }
    }
    for (int i = 0; i < n; i++){
        if (i != max_idx){
            sum += exp(x[i] - max);
        }
    }


    sum = max + log(sum+1);
    return sum;
}

