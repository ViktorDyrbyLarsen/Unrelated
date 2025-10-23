#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double trlndet(int n, double * T);

int main(void)
{
    double T[9] = {1, 2, 3, 0, -4, 5, 0, 0, -6};
    double lndetT = trlndet(3, T);
    printf("lndet(T) = %.9g\n", lndetT);

    return EXIT_SUCCESS;
}
