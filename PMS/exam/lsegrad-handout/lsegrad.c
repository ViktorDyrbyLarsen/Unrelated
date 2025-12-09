#include <stdlib.h>
#include <math.h>

int lsegrad(double * x, int n)
{
    if (!x || n <= 0) return 1;

    double max = x[0];
    int maxidx = 0;
    for (int i = 1; i < n){
        
    }

    double sum = 0;
    for (int i = 0; i < n; i++){
        if (isnan(x[i])) return -1;
        sum += exp(x[i]);
        x[i] = exp(x[i]);
    }


    for (int i = 0; i < n; i++){
        x[i] /= sum;  
    }

    return 0;

}