// 02635 Final exam (E25)
// Template for part 2/2, Question 3b

#include <stdlib.h>
#include <math.h>

int dsr1sv(int n, const double * a, const double * b, double * x) 
{
    if (!a || !b || !x || n<0) return -1;
    double const1 = 1;  // 1 + b.T A.inv * b).inv()
    double * array1 = malloc(n*sizeof(double));

    for (int i = 0; i < n; i++){
        if (a[i] <= 0) return -1;
        const1 += a[i] * b[i] * b[i];
    }
    const1 = 1/const1;

    for (int row = 0; row<n;row++){
        for (int col = 0; col<n; col++){
            array1[row] += b[row] * b[col] * x[col] / (a[row] * a[col]);
        }
    }
    for (int i = 0; i < n; i++){
        x[i] = 1/a[i] - array1[i]*const1;
    }
    free(array1);
    return 0;
}