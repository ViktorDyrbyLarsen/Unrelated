#include <stdlib.h>
#include <stdio.h>

int dsr1mv(int n, const double * a, const double * b, double * x);

int main(int argc, char *argv[])
{
    int n = 5;
    const double a[] = {1,2,3,4,5};
    const double b[] = {6,7,8,9,10};
    double x[] = {1,1,1,1,1};
    double result = dsr1mv(n,a,b,x);
    for (int i = 0; i<n; i++){
        printf("%f \n", x[i]);
    }
    
    return 0;
}