// 02635 Final exam (E25)
// Template for part 2/2, Question 3a

#include <stdlib.h>
#include <math.h>
int dsr1mv(int n, const double * a, const double * b, double * x) 
{
    if (!a||!b||!x||n<0) return -1;

    double * Mx = malloc(sizeof(double) * n);
    double * bx = malloc(sizeof(double) * n);
    
    for (int i = 0; i<n;i++){
        for (int j = 0; j<n; j++){
            bx[i] += b[i]*b[j]*x[j];
        }
        Mx[i] = a[i] * x[i] + bx[i];
    }

    for (int i = 0; i<n; i++){
        x[i] = Mx[i];
    }
    
    free(Mx);
    free(bx);
    return 0;
}